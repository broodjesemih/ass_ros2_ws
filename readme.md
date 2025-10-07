# 🎓 Tilmann's Cijfer Generator - ROS2 Project

Een geautomatiseerd cijfersysteem gebouwd met ROS2 dat tentamenresultaten genereert, eindcijfers berekent en herkansingen plant voor studenten.

## 📋 Inhoudsopgave
- [🚀 Snelstart](#-snelstart)
- [📦 Installatie voor Beginners](#-installatie-voor-beginners)
- [⚙️ Project Opzetten](#️-project-opzetten)
- [🏃‍♂️ Het Systeem Draaien](#️-het-systeem-draaien)
- [👁️ Individuele Nodes Bekijken en Draaien](#️-individuele-nodes-bekijken-en-draaien)
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

# 4. Run alles via de launchfile
ros2 launch g1_ass1_pkg system.launch.xml

# of, run het via 5 individuele terminals, waarvoor de dependancy tmux nodig is
sudo apt install tmux
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

### Start het volledige systeem met één commando:
```bash
ros2 launch g1_ass1_pkg system.launch.xml
```

of, run het via 5 individuele terminals, waarvoor de dependancy tmux nodig is
```bash
sudo apt install tmux
./run.sh
```


Dit start automatisch alle nodes:
- `tentamen_result_generator`
- `cijfer_calculator`
- `final_cijfer_determinator`
- `herkansing_scheduler`
- `herkansing_cijfer_determinator`

### Stoppen:
Gebruik **Ctrl + C** om alles tegelijk af te sluiten.

---

## 👁️ Individuele Nodes Bekijken en Draaien

### 1. Alle beschikbare nodes bekijken
```bash
ros2 node list
```

### 2. Individuele node starten
Bijvoorbeeld om alleen de `tentamen_result_generator` te draaien:
```bash
cd ~/g1_assessment1_ros2
source install/setup.bash
ros2 run g1_ass1_pkg tentamen_result_generator
```

### 3. Node-info bekijken
```bash
ros2 node info /tentamen_result_generator
```

### 4. Actieve topics bekijken
```bash
ros2 topic list
```

### 5. Data van een topic inspecteren
```bash
ros2 topic echo /tentamen_results
```

### 6. Services bekijken
```bash
ros2 service list
```

### 7. Services aanroepen
Bijvoorbeeld:
```bash
ros2 service call /calculate_cijfer g1_interface_pkg/srv/CalculateCijfer "{student_id: 1}"
```


## 📁 Project Structuur

```
g1_assessment1_ros2/
├── README.md
├── database.sqlite
├── src/
│   ├── g1_interface_pkg/
│   │   ├── msg/
│   │   ├── srv/
│   │   ├── action/
│   ├── g1_ass1_pkg/
│   │   ├── src/
│   │   ├── launch/
│   │   │   └── system.launch.xml
│   │   ├── CMakeLists.txt
│   │   └── package.xml
```

---

## 💾 Database

### Bekijken
```bash
# Installeer sqlite3 als je het nog niet hebt
sudo apt install sqlite3

# Open de database
sqlite3 database.sqlite
.headers on
.mode column
SELECT * FROM student_results;
```

---

## 🐛 Troubleshooting

#### ❌ "file 'system.launch.xml' was not found"
Controleer of het bestand zich bevindt in:
```
src/g1_ass1_pkg/launch/system.launch.xml
```

#### ❌ "Package not found"
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

**Nout Mulder**, **Semih Can Karakoc**, **Tycho Mallee**