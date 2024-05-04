# telemetry-formula-SAE
This repo contains LoRa telemetry firmware and software for Virginia Motorsports' Formula SAE car.

## Motivation

The concept of this project is to provide an extensible and flexible telemetry system over LoRa. LoRa is a long range, low footprint option for telemetry. Unlike 5G (which is standard on racing series such as the Indy Autonomous Challenge (IAC)), it does not require cell service. LoRa is highly power efficient and resistant to electronic interference, unlike WiFi. It is also less affected by multiple other racing teams using WiFi at the same time, as it has frequency spreading. These characteristics make it well suited to the Formula SAE student electric racecar competition.

## Goals

The main goal of this project is to provide a highly scalable solution. As new cars are constructed every year for the Formula competition at the University of Virginia, requirements for telemetry change and grow annually. For example, in 2024, the team shifted from an internal combusion-driven car to an electric powertrain. This shift drastically changed the type of data generated by the car's computer systems. Now, it has to account for high voltage electrical systems in addition to a low (12V) voltage system. Also, as the team pushes the envelope in terms of performance and driver training, data analytics teams have increased demand for detailed, high-frequency data.

Examples of how telemetry data might be used to enhance the vehicle:
- Evaluate how a change in aerodynamics impacts performance
- Evaluate different driver techniques in a certain event


## Implementation

- Two Heltec LoRa 32 v3 boards are used. One is connected via USB to a base station (in our case, a laptop running Ubuntu). The other is connected via USB to the car-board computer (in our case, a Jetson module). The folder /P2P_lora_formula contains embedded code running on the Heltec board connected to the car-board computer. /P2P_lora_receiver_formula contains embedded code running on the Heltec board connected to the base station.
- A software interface written in QT displays the live data as it is received and has functions to save it. This code is in /base_station and runs on the base station.
- We define an extensible packet format.
- Uses RadioLib
