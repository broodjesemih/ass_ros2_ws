# 🎓 ROS2 Cijfer Generator

Een geautomatiseerd cijfersysteem gebouwd met **ROS2 Jazzy** en **PostgreSQL**.

## 🚀 Quick Start

**Heb je ROS2 Jazzy + Docker al?**

```bash
git clone https://github.com/broodjesemih/ass_ros2_ws.git
cd ass_ros2_ws
bash quick_test.sh
```

**Dat is alles!** Het systeem start automatisch en draait 60 seconden. ✅

## 🔧 Installatie (Voor Beginners)

### Linux (Ubuntu 22.04/24.04)

```bash
# 1. ROS2 Jazzy installeren
sudo apt update && sudo apt upgrade -y
sudo apt install software-properties-common curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list
sudo apt update && sudo apt install ros-jazzy-desktop python3-colcon-common-extensions libpq-dev -y
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

# 2. Docker installeren
curl -fsSL https://get.docker.com -o get-docker.sh && sudo sh get-docker.sh
sudo usermod -aG docker $USER && newgrp docker

# 3. Project starten
git clone https://github.com/broodjesemih/ass_ros2_ws.git
cd ass_ros2_ws && bash quick_test.sh
```

### Windows (WSL2)

```powershell
# 1. WSL2 installeren (PowerShell als Administrator)
wsl --install -d Ubuntu-24.04
# Herstart computer, open Ubuntu app

# 2. Docker Desktop installeren
# Download van https://www.docker.com/products/docker-desktop/
# Enable WSL2 integration in Docker settings

# 3. In Ubuntu terminal, volg Linux stappen hierboven
```

### macOS

```bash
# 1. Dependencies installeren
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install ros2-jazzy postgresql libpq docker

# 2. Environment setup
echo "source /opt/homebrew/opt/ros2-jazzy/setup.bash" >> ~/.zshrc
source ~/.zshrc

# 3. Project starten
git clone https://github.com/broodjesemih/ass_ros2_ws.git
cd ass_ros2_ws && bash quick_test.sh
```

## 🎮 Gebruiken

### Snelle Test
```bash
bash quick_test.sh          # 60 seconden complete test
```

### Handmatig
```bash
docker compose up -d        # Start database
bash run.sh                 # Build project
ros2 launch g1_ass1_pkg cijfer_system.launch.py  # Start systeem
```

### Stoppen
```bash
pkill -f ros2              # Stop alle nodes
docker compose down        # Stop database (optioneel)
```

## 📊 Wat Doet Het?

Het systeem simuleert een complete cijfer workflow:

1. **📝 Tentamen Generator** → Genereert random tentamen resultaten
2. **🧮 Cijfer Calculator** → Berekent eindcijfers (1-10 schaal)
3. **💾 Database Opslag** → Slaat alles op in PostgreSQL
4. **🔄 Herkansing Planner** → Plant herkansingen voor gezakte studenten

**Live voorbeeld:**
```
[INFO] Published tentamen for Semih/ROS2: 73
[INFO] Calculated final cijfer for Semih/ROS2: 74
✅ SAVED final result for Semih in ROS2: 74
```

## 🔍 Database Bekijken

```bash
# Verbind naar database
docker exec -it cijfer_generator_db psql -U postgres -d cijfer_generator

# Bekijk resultaten
SELECT * FROM student_results ORDER BY created_at DESC LIMIT 10;

# Exit
\q
```

## 📁 Project Structuur

```
ass_ros2_ws/
├── quick_test.sh                    # Snelle launcher
├── docker-compose.yml              # PostgreSQL setup
├── src/g1_ass1_pkg/                # Hoofdapplicatie
│   ├── src/*.cpp                   # C++ broncode (5 nodes)
│   └── launch/cijfer_system.launch.py  # ROS2 launch file
└── src/g1_interface_pkg/           # Custom ROS2 messages
```

## 🐛 Problemen?

**"ros2: command not found"**
```bash
source /opt/ros/jazzy/setup.bash
```

**Database problemen**
```bash
docker compose restart cijfer_generator_db
```

**Build errors**
```bash
sudo apt install libpq-dev
rm -rf build install log && colcon build
```

## 📚 Meer Info

- **📖 Volledige documentatie**: [DOCUMENTATION.md](DOCUMENTATION.md)
- **🐛 Issues**: [GitHub Issues](https://github.com/broodjesemih/ass_ros2_ws/issues)
- **🤝 Bijdragen**: Fork → Feature branch → Pull Request

## 🎯 Features

✅ **5 ROS2 Nodes** - Complete modulaire architectuur  
✅ **PostgreSQL Database** - Robuuste data opslag  
✅ **Docker Integration** - Eenvoudige database setup  
✅ **Cross-platform** - Windows, Linux, macOS  
✅ **Official Launch Files** - Professional ROS2 workflow  
✅ **Real-time Processing** - Live cijfer verwerking  

## 📞 Contact

- **GitHub**: [broodjesemih/ass_ros2_ws](https://github.com/broodjesemih/ass_ros2_ws)
- **Issues**: Voor bugs en feature requests

---

**Made with ❤️ using ROS2 Jazzy, PostgreSQL & Docker**
