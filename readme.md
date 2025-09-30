# Tilmann's Cijfer Generator - ROS2 Project

Dit project automatiseert het cijferproces voor studenten en bestaat uit meerdere ROS2 nodes en één interface package. Hieronder vind je uitleg per node en hoe deze samen werken via ROS2 interfaces.

---

## Packages

- **g1_interface_pkg**  
  Bevat alle ROS2 interfaces:  
  - `msg/Student.msg`  
  - `msg/Tentamen.msg`  
  - `srv/Tentamens.srv`  
  - `action/Herkanser.action`

- **g1_ass1_pkg**  
  Bevat alle logica/nodes:
  - `tentamen_result_generator.cpp`
  - `final_cijfer_determinator.cpp`
  - `cijfer_calculator.cpp`
  - `herkansing_scheduler.cpp`
  - `herkansing_cijfer_determinator.cpp`

---

## Node Uitleg

### 1. tentamen_result_generator.cpp

- **Doel:** Genereert willekeurige tentamen cijfers voor student/course combinaties waarvoor nog geen eindcijfer bestaat.
- **Interactie:**  
  - Leest combinaties uit `database.sqlite`.
  - Publiceert elke 2 seconden een `Tentamen` bericht op het topic `/tentamen_results`.
- **Interface:**  
  - Gebruikt `g1_interface_pkg/msg/Tentamen`.

---

### 2. final_cijfer_determinator.cpp

- **Doel:** Verzamelt tentamen cijfers per student/course combinatie en vraagt het eindcijfer aan.
- **Interactie:**  
  - Subscribed op `/tentamen_results`.
  - Slaat cijfers op tot er er 3 zijn.
  - Vraagt via de service `/calculate_final_cijfer` het eindcijfer aan.
  - Schrijft het resultaat naar `database.sqlite`.
- **Interface:**  
  - Gebruikt `g1_interface_pkg/msg/Tentamen` (sub).
  - Gebruikt `g1_interface_pkg/srv/Tentamens` (client).

---

### 3. cijfer_calculator.cpp

- **Doel:** Rekent het eindcijfer uit op basis van een lijst tentamen cijfers.
- **Interactie:**  
  - Draait als service `/calculate_final_cijfer`.
  - Ontvangt een request met student, course en cijfers.
  - Berekent het gemiddelde, geeft Wessel +10 bonus, clamped tussen 10 en 100.
  - Stuurt het eindcijfer terug.
- **Interface:**  
  - Gebruikt `g1_interface_pkg/srv/Tentamens` (service).

---

### 4. herkansing_scheduler.cpp

- **Doel:** Zoekt regelmatig in de database naar studenten die gezakt zijn (cijfer tussen 10 en 54) en start een herkansing.
- **Interactie:**  
  - Leest `database.sqlite`.
  - Stuurt een goal naar de action server `/herkanser` voor elke herkansing.
- **Interface:**  
  - Gebruikt `g1_interface_pkg/action/Herkanser` (action client).

---

### 5. herkansing_cijfer_determinator.cpp

- **Doel:** Voert een herkansing uit voor een student/course combinatie.
- **Interactie:**  
  - Ontvangt een goal via de action server `/herkanser`.
  - Genereert opnieuw 3 willekeurige tentamen cijfers.
  - Vraagt via de service `/calculate_final_cijfer` het nieuwe eindcijfer aan.
  - Schrijft het nieuwe resultaat naar `database.sqlite` (oude resultaat blijft staan).
- **Interface:**  
  - Gebruikt `g1_interface_pkg/action/Herkanser` (action server).
  - Gebruikt `g1_interface_pkg/srv/Tentamens` (client).

---

## Interfaces

- **Student.msg:**  
  Bevat een student/course combinatie en een ROS2 timestamp.

- **Tentamen.msg:**  
  Bevat een student/course combinatie, tentamen cijfer en een ROS2 timestamp.

- **Tentamens.srv:**  
  Request: student_name, course_name, lijst van tentamen cijfers  
  Response: eindcijfer, bericht

- **Herkanser.action:**  
  Goal: student_name, course_name  
  Result: eindcijfer, bericht  
  Feedback: voortgang, status

---

## Database

- **Bestand:** `/ass_ros2_ws/database.sqlite`
- **Structuur:**  
  `student_name,course_name,number_of_exams,final_result,timestamp`

---

## Gebruik

1. **Build de workspace:**  

   ```sh
   colcon build
   source install/setup.bash
   ```

2. **Start de nodes in aparte terminals:**  

   ```sh
   ros2 run g1_ass1_pkg tentamen_result_generator
   ros2 run g1_ass1_pkg final_cijfer_determinator
   ros2 run g1_ass1_pkg cijfer_calculator
   ros2 run g1_ass1_pkg herkansing_scheduler
   ros2 run g1_ass1_pkg herkansing_cijfer_determinator
   ```

3. **Bekijk de database en logging om het proces te volgen.**

---

## Overzicht interactie

- **tentamen_result_generator** → `/tentamen_results` → **final_cijfer_determinator** → `/calculate_final_cijfer` → **cijfer_calculator** → database
- **herkansing_scheduler** → `/herkanser` (goal) → **herkansing_cijfer_determinator** → `/calculate_final_cijfer` → **cijfer_calculator** → database

---
ni ni ni nickelodeon
