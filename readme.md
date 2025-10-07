# 🎓 Tilmann's Cijfer Generator - ROS2 Project

Een geautomatiseerd cijfersysteem gebouwd met ROS2 dat tentamenresultaten genereert, eindcijfers berekent en herkansingen plant voor studenten.

## 📋 Inhoudsopgave
- [🚀 Snelstart](#-snelstart)
- [📦 Installatie voor Beginners](#-installatie-voor-beginners)
- [⚙️ Project Opzetten](#️-project-opzetten)
- [🏃‍♂️ Het Systeem Draaien](#️-het-systeem-draaien)
- [🔍 Wat Doet Dit Project?](#-wat-doet-dit-project)
- [📁 Project Structuur](#-project-structuur)
- [🧩 ROS2 Nodes Uitleg](#-ros2-nodes-uitleg)
- [🔌 ROS2 Interfaces](#-ros2-interfaces)
- [💾 Database](#-database)
- [🐛 Troubleshooting](#-troubleshooting)

---

## 🚀 Snelstart

Als je al ROS2 hebt geïnstalleerd:

```bash
# 1. Clone het project
git clone https://github.com/broodjesemih/ass_ros2_ws.git g1_assessment1_ros2
cd g1_assessment1_ros2

# 2. Build het project
colcon build

# 3. Source de workspace
source install/setup.bash

# 4. Run alles tegelijk (Linux/Mac)
./run.sh
```



---

## 📦 Installatie voor Beginners

### Stap 1: ROS2 Installeren

#### Voor Ubuntu 24.04 (Jazzy):
```bash
# Update je systeem
sudo apt update && sudo apt upgrade -y

# Installeer ROS2 Jazzy
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt install curl gnupg lsb-release

# Voeg ROS 2 GPG key toe
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

# Voeg repository toe
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Installeer ROS2
sudo apt update
sudo apt install ros-jazzy-desktop python3-colcon-common-extensions

# Setup environment
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

**Let op:** Dit project is getest op Ubuntu 24.04 met ROS2 Jazzy.

### Stap 2: Extra Dependencies
```bash
# Installeer build tools
sudo apt install python3-pip python3-rosdep
pip3 install colcon-common-extensions

# Initialiseer rosdep (eenmalig)
sudo rosdep init
rosdep update
```

---

## ⚙️ Project Opzetten

### Stap 1: Repository Clonen
```bash
# Clone het project in de juiste map
git clone https://github.com/broodjesemih/ass_ros2_ws.git g1_assessment1_ros2
cd g1_assessment1_ros2
```

### Stap 2: Dependencies Installeren
```bash
# Installeer alle dependencies automatisch
rosdep install --from-paths src --ignore-src -r -y
```

### Stap 3: Project Builden
```bash
# Build alle packages
colcon build

# Als je problemen krijgt, probeer:
colcon build --cmake-clean-cache
```

### Stap 4: Workspace Activeren
```bash
# Source de workspace (dit moet je elke keer doen in een nieuwe terminal)
source install/setup.bash

# Alternatief: Source de workspace (zsh ipv bash)
source install/setup.zsh

# Of voeg het toe aan je .bashrc (of .zshrc) voor permanente activatie:
echo "source $(pwd)/install/setup.bash" >> ~/.bashrc
```

---

## 🏃‍♂️ Het Systeem Draaien

### Optie A: Automatisch met Script
```bash
# Maak het script uitvoerbaar
chmod +x run.sh

# Start alle nodes in een tmux sessie
./run.sh
```

### Optie B: Handmatig

Open **5 aparte terminals** en voer in elke terminal uit:

#### Terminal 1: Tentamen Result Generator
```bash
cd ~/g1_assessment1_ros2
source install/setup.bash
ros2 run g1_ass1_pkg tentamen_result_generator
```

#### Terminal 2: Cijfer Calculator
```bash
cd ~/g1_assessment1_ros2
source install/setup.bash
ros2 run g1_ass1_pkg cijfer_calculator
```

#### Terminal 3: Final Cijfer Determinator
```bash
cd ~/g1_assessment1_ros2
source install/setup.bash
ros2 run g1_ass1_pkg final_cijfer_determinator
```

#### Terminal 4: Herkansing Scheduler
```bash
cd ~/g1_assessment1_ros2
source install/setup.bash
ros2 run g1_ass1_pkg herkansing_scheduler
```

#### Terminal 5: Herkansing Cijfer Determinator
```bash
cd ~/g1_assessment1_ros2
source install/setup.bash
ros2 run g1_ass1_pkg herkansing_cijfer_determinator
```



---

## 🔍 Wat Doet Dit Project?

Dit systeem simuleert een automatisch cijfersysteem voor een school:

1. **Tentamen Generatie**: Genereert willekeurige tentamencijfers voor studenten
2. **Cijfer Berekening**: Berekent eindcijfers op basis van 3 tentamens
3. **Herkansing Systeem**: Plant automatisch herkansingen voor gezakte studenten
4. **Database Opslag**: Slaat alle resultaten op in een SQLite database

### Flow van het Systeem:
```
Tentamen Generator → Publiceert cijfers → Final Cijfer Determinator
                                                    ↓
Database ← Cijfer Calculator ← Service Request ←────┘
    ↑                                               
    └── Herkansing Cijfer Determinator ← Action ← Herkansing Scheduler
```

---

## 📁 Project Structuur

```
g1_assessment1_ros2/
├── readme.md                    # Dit bestand
├── run.sh                      # Automatisch start script
├── database.sqlite             # Database (wordt automatisch aangemaakt)
└── src/
    ├── g1_interface_pkg/       # ROS2 Interfaces (msg, srv, action)
    │   ├── msg/
    │   │   ├── Student.msg
    │   │   └── Tentamen.msg
    │   ├── srv/
    │   │   └── Tentamens.srv
    │   ├── action/
    │   │   └── Herkanser.action
    │   ├── CMakeLists.txt
    │   └── package.xml
    └── g1_ass1_pkg/           # Alle node implementaties
        ├── src/
        │   ├── tentamen_result_generator.cpp
        │   ├── final_cijfer_determinator.cpp
        │   ├── cijfer_calculator.cpp
        │   ├── herkansing_scheduler.cpp
        │   ├── herkansing_cijfer_determinator.cpp
        │   └── database.cpp
        ├── CMakeLists.txt
        └── package.xml
```

---

## 🧩 ROS2 Nodes Uitleg

### 1. 🎯 tentamen_result_generator.cpp
- **Functie**: Genereert willekeurige tentamencijfers (10-100) voor student/course combinaties
- **Timing**: Publiceert elke 2 seconden een nieuw tentamenresultaat
- **ROS2 Interface**: Publisher op topic `/tentamen_results`
- **Database Interactie**: Leest student/course combinaties uit database

### 2. 📊 final_cijfer_determinator.cpp  
- **Functie**: Verzamelt 3 tentamencijfers per student en vraagt eindcijfer aan
- **ROS2 Interface**: 
  - Subscriber op `/tentamen_results`
  - Service client voor `/calculate_final_cijfer`
- **Database Interactie**: Schrijft eindresultaten naar database

### 3. 🧮 cijfer_calculator.cpp
- **Functie**: Berekent eindcijfer op basis van tentamencijfers
- **Berekening**: Gemiddelde van 3 cijfers + speciale bonus voor "Wessel" (+10 punten)
- **ROS2 Interface**: Service server `/calculate_final_cijfer`
- **Range**: Cijfers worden begrensd tussen 10-100

### 4. 📅 herkansing_scheduler.cpp
- **Functie**: Zoekt gezakte studenten (cijfer 10-54) en plant herkansingen
- **Timing**: Controleert elke X seconden de database
- **ROS2 Interface**: Action client voor `/herkanser`
- **Database Interactie**: Leest eindresultaten uit database

### 5. 🔄 herkansing_cijfer_determinator.cpp
- **Functie**: Voert herkansing uit door nieuwe cijfers te genereren
- **ROS2 Interface**: 
  - Action server `/herkanser`
  - Service client voor `/calculate_final_cijfer`
- **Database Interactie**: Schrijft nieuwe herkansingsresultaten

---

## 🔌 ROS2 Interfaces

### Messages (msg/)

#### Student.msg
```
string student_name
string course_name
builtin_interfaces/Time timestamp
```

#### Tentamen.msg
```
string student_name
string course_name
int32 cijfer
builtin_interfaces/Time timestamp
```

### Services (srv/)

#### Tentamens.srv
```
# Request
string student_name
string course_name
int32[] cijfers

---
# Response
int32 eindcijfer
string bericht
```

### Actions (action/)

#### Herkanser.action
```
# Goal
string student_name
string course_name

---
# Result
int32 eindcijfer
string bericht

---
# Feedback
string voortgang
string status
```

---

## 💾 Database

### Database Bestand
- **Locatie**: `g1_assessment1_ros2/database.sqlite`
- **Type**: SQLite database
- **Auto-creatie**: Wordt automatisch aangemaakt als het niet bestaat

### Database Schema
```sql
CREATE TABLE results (
    student_name TEXT,
    course_name TEXT,
    number_of_exams INTEGER,
    final_result INTEGER,
    timestamp TEXT
);
```

### Database Inhoud Bekijken
```bash
# Installeer sqlite3 als je het nog niet hebt
sudo apt install sqlite3

# Open de database
sqlite3 database.sqlite

# Bekijk alle resultaten
.mode column
.headers on
SELECT * FROM results;

# Verlaat sqlite3
.quit
```

---

## 🐛 Troubleshooting

### Veel Voorkomende Problemen

#### ❌ "Package not found" Error
```bash
# Oplossing: Source je workspace opnieuw
source install/setup.bash

# Of rebuild het project
colcon build
source install/setup.bash
```

#### ❌ "No executable found" Error
```bash
# Controleer of de build succesvol was
colcon build --cmake-clean-cache

# Check of executables bestaan
ls install/g1_ass1_pkg/lib/g1_ass1_pkg/
```

#### ❌ Database Permission Error
```bash
# Geef write permissions aan de database directory
chmod 755 .
chmod 666 database.sqlite  # Als het al bestaat
```

#### ❌ Nodes starten niet
```bash
# Check of alle dependencies geïnstalleerd zijn
rosdep install --from-paths src --ignore-src -r -y

# Rebuild het project
colcon build
```

#### ❌ "Interface not found" Error
```bash
# Build de interface package eerst
colcon build --packages-select g1_interface_pkg
source install/setup.bash

# Dan build de rest
colcon build
```

### Debug Commando's

#### Controleer actieve nodes
```bash
ros2 node list
```

#### Bekijk topics
```bash
ros2 topic list
ros2 topic echo /tentamen_results
```

#### Bekijk services
```bash
ros2 service list
ros2 service call /calculate_final_cijfer g1_interface_pkg/srv/Tentamens "{student_name: 'Test', course_name: 'Math', cijfers: [80, 90, 85]}"
```

#### Bekijk actions
```bash
ros2 action list
```

#### Monitor systeem logs
```bash
# In een aparte terminal
ros2 log level set /tentamen_result_generator DEBUG
```

---

## 📊 Monitoring en Testing

### Real-time Monitoring
```bash
# Monitor alle topic communicatie
ros2 topic echo /tentamen_results

# Monitor service calls
ros2 service call /calculate_final_cijfer g1_interface_pkg/srv/Tentamens "{student_name: 'TestStudent', course_name: 'TestCourse', cijfers: [75, 80, 85]}"

# Bekijk system status
ros2 node info /tentamen_result_generator
```

### Database Monitoring
```bash
# Bekijk real-time database changes
watch -n 2 'sqlite3 database.sqlite "SELECT * FROM results ORDER BY timestamp DESC LIMIT 10;"'
```

---

## 🎯 Verwachte Output

Wanneer het systeem draait, verwacht je de volgende output:

1. **Tentamen Generator**: "Publishing tentamen result for [student] in [course]: [cijfer]"
2. **Final Cijfer Determinator**: "Received 3 cijfers for [student], calculating final result..."
3. **Cijfer Calculator**: "Calculated final cijfer [X] for [student] in [course]"
4. **Herkansing Scheduler**: "Found failed student [student], scheduling herkanser..."
5. **Database**: Nieuwe entries verschijnen in de results tabel


---

## 📄 Licentie

Dit project valt onder de MIT License.

---

## 👨‍💻 Auteurs

**[Nout Mulder](https://github.com/noutmulder) | [Semih Can Karakoc](https://github.com/broodjesemih) | [Tycho Mallee](https://github.com/tyrhaton)** 


---

*Voor vragen of problemen, open een issue op GitHub of neem contact op via een van de auteurs!*
