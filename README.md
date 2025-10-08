# ROS2 Grade Calculator System

Een complete ROS2-gebaseerde cijfer calculator met PostgreSQL database backend.

## 🚀 Quick Start (Een script doet alles!)

```bash
# Download het project
git clone <repository-url>
cd ass_ros2_ws

# Run het complete setup script (werkt op alle Linux distributies)
./complete_setup.sh

# Start het systeem
./run_system.sh
```

Dat is alles! Het `complete_setup.sh` script detecteert automatisch je Linux distributie en installeert alles wat nodig is.

## 📋 Wat doet het systeem?

Dit systeem simuleert een cijfer calculator voor studenten met de volgende componenten:

- **tentamen_result_generator**: Genereert tentamen resultaten
- **cijfer_calculator**: Berekent cijfers gebaseerd op resultaten  
- **final_cijfer_determinator**: Bepaalt eindcijfers
- **herkansing_scheduler**: Plant herkansingen
- **herkansing_cijfer_determinator**: Handelt herkansing cijfers af

## 🔧 Ondersteunde Linux Distributies

Het setup script werkt automatisch op:

- ✅ **Ubuntu** (20.04, 22.04, 24.04)
- ✅ **Debian** (11, 12)
- ✅ **Linux Mint**
- ✅ **Pop!_OS**
- ✅ **Fedora** (38, 39, 40)
- ✅ **RHEL/CentOS/Rocky/AlmaLinux**
- ✅ **openSUSE/SLES**
- ✅ **Arch Linux/Manjaro**

## 🛠️ Wat wordt geïnstalleerd?

Het script installeert automatisch:

1. **PostgreSQL** + ontwikkel libraries
2. **libpqxx** (PostgreSQL C++ library)
3. **ROS2 Jazzy** (als niet aanwezig)
4. **Build tools** (cmake, gcc, etc.)
5. **Database setup** met gebruikers en authenticatie

## 📁 Project Structuur

```
ass_ros2_ws/
├── complete_setup.sh          # 🎯 HOOFDSCRIPT - doet alles!
├── run_system.sh              # 🚀 Start het systeem (automatisch aangemaakt)
├── test_database.sh           # 🔍 Test database connectie (automatisch aangemaakt)
├── src/
│   ├── g1_ass1_pkg/           # Hoofdproject
│   │   ├── src/               # C++ broncode
│   │   ├── launch/            # ROS2 launch bestanden
│   │   └── CMakeLists.txt     # Build configuratie
│   └── g1_interface_pkg/      # Custom ROS2 interfaces
├── install/                   # Gebouwde bestanden
├── build/                     # Build cache
└── log/                       # Build logs
```

## 🎮 Gebruik

### Systeem starten
```bash
./run_system.sh
```

### Database testen
```bash
./test_database.sh
```

### Handmatig builden
```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select g1_ass1_pkg
```

### Handmatig starten
```bash
source install/setup.bash
ros2 launch g1_ass1_pkg system.launch.xml
```

## 🐛 Troubleshooting

### PostgreSQL problemen
```bash
# Check status
sudo systemctl status postgresql

# Herstart service
sudo systemctl restart postgresql

# Check logs
sudo journalctl -u postgresql
```

### ROS2 problemen
```bash
# Rebuild project
colcon build --packages-select g1_ass1_pkg

# Check ROS2 environment
echo $ROS_DISTRO

# Source manually
source /opt/ros/jazzy/setup.bash
source install/setup.bash
```

### Database connectie problemen
```bash
# Test handmatig
psql -h localhost -U postgres -d student_grades

# Check socket files
ls -la /var/run/postgresql/
ls -la /tmp/.s.PGSQL.*
```

## 🔑 Database Details

- **Database**: `student_grades`
- **Gebruiker**: `postgres`  
- **Wachtwoord**: `password`
- **Host**: `localhost`
- **Port**: `5432`

## 📞 Support

Als je problemen hebt:

1. **Run eerst**: `./complete_setup.sh` opnieuw
2. **Check logs**: De script geeft duidelijke foutmeldingen
3. **Test database**: `./test_database.sh`
4. **Check services**: `sudo systemctl status postgresql`

## 🎯 Voor Ontwikkelaars

### Custom interfaces
Het project gebruikt custom ROS2 interfaces gedefinieerd in `g1_interface_pkg`.

### Database schema
```sql
CREATE TABLE student_results (
    id SERIAL PRIMARY KEY,
    student_name VARCHAR(255) NOT NULL,
    course VARCHAR(255) NOT NULL,
    number_of_exams INTEGER,
    final_result REAL,
    timestamp BIGINT
);
```

### Connectie logica
De applicatie probeert automatisch verschillende connectie methoden:
1. TCP met wachtwoord
2. Unix socket met huidige gebruiker  
3. Peer authenticatie
4. Eenvoudige lokale connectie

---

**Gemaakt voor TI Minor Cijfer Generator systeem** 🎓
