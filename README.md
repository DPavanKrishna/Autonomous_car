# Autonomous Car Project - Navigating the Future with C++ Programming

## Project Overview

This repository contains the implementation of an **Autonomous Car System** using **C++**, focusing on obstacle detection and avoidance. The car is equipped with ultrasonic sensors, motors, and a steering servo, allowing both manual and autonomous operation. The project simulates a foundational approach to autonomous vehicle systems, providing insights into robotics and programming integration.

---

## **Objective**
To design and implement an autonomous car system that:
- Detects obstacles using an **ultrasonic sensor**.
- Navigates around obstacles autonomously using motors and a steering servo.
- Offers manual control via a **serial interface**.

---

## **System Components**
1. **Ultrasonic Sensor**: Measures distances to obstacles.
2. **DC Motors**: Drive the car forward, backward, or stop.
3. **Servo Motor**: Controls the car's steering direction.
4. **Microcontroller (e.g., Arduino)**: Processes sensor inputs, controls motors, and manages user commands.

---

## **System Inputs and Outputs**

### **Inputs**
- Distance data from the **ultrasonic sensor**.
- Serial commands from the user (e.g., "start", "exit").

### **Outputs**
- Motor control actions: Forward, backward, stop.
- Steering commands: Turn left, turn right, or stay straight.

---

## **Behavioral Logic**

### **Idle State**
- The car remains stationary until it receives a "start" command.

### **Obstacle Detection Logic**
1. **Distance > 20 cm**: Move forward.
2. **Distance ≤ 20 cm**:
   - **10 cm < Distance ≤ 20 cm**: Stop and turn right.
   - **Distance ≤ 10 cm**: Stop and turn left.

### **Manual Control**
- The user can override autonomous behavior using serial commands to start or stop the car.

---

## **Flow Diagram**
```
[ Start ] --> [ Wait for User Input ]
                  |
         [ User Command? ]
              /   \
           Yes     No
            |       |
       [ Start ]   [ Read Distance ]
            |       |
      [ Move Forward ] ------> [ Check Distance ]
            |                      |
          [ Obstacle? ] -------> [ Turn/Stop ]
           /   \
         Yes    No
          |      |
     [ Stop ]  [ Move Forward ]
```

---

## **Circuit Design**
| Sensor Distance (cm) | User Command | Motor State       | Steering Action |
|-----------------------|--------------|-------------------|-----------------|
| > 20                 | start        | Moving Forward    | Straight        |
| ≤ 20 and > 10        | start        | Stopped           | Turn Right      |
| ≤ 10                 | start        | Stopped           | Turn Left       |
| -                    | exit         | Stopped           | -               |

---

## **Simulation Results**
1. **Moving Forward**: No obstacles detected (**distance > 20 cm**).
2. **Turning Left**: Obstacle detected (**distance ≤ 10 cm**).
3. **Turning Right**: Obstacle detected (**10 cm < distance ≤ 20 cm**).

---

## **Challenges and Solutions**
1. **Sensor Accuracy**: Addressed by averaging multiple readings.
2. **Motor Control**: Smooth transitions achieved by optimizing delays and speeds.
3. **User Input Handling**: Prioritized sensor checks over user commands for seamless operation.

---

## **Conclusion**
The project successfully demonstrates a basic autonomous car system capable of detecting obstacles and navigating accordingly. 

### **Future Enhancements**
- Additional sensors for improved navigation.
- Machine learning for smarter decision-making.
- GPS integration for outdoor navigation.

---

## **Usage**
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/autonomous-car-project.git
   ```
2. Follow the instructions in the **PROCEDURAL PROGRAMMING WITH C.docx** for setup and execution.

### **Files**
- `c++ file.cpp`: Source code of the project.
- `PROCEDURAL PROGRAMMING WITH C.docx`: Documentation detailing the project.
- `The-Autonomous-Car-Project.pptx`: Presentation slides summarizing the system design.

---

Enjoy building your autonomous car system! 🚗
