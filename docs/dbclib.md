---
layout: default
title: DBC C++ Library
---

# Overview of the DBC C++ Library

The library is used to read in and parse a DBC file. The DBC file describes devices, messages and signals for a CAN
network. The following interface exist.

- **DbcFile**. Main object that reads in and parse a DBC file. The DBC file may contain one or more networks.
- **Network**. Information about the CAN network. Basic is the CAN Protocol (ProtocolType) in use (example J1939). 
- **Node**. Defines a device (ECU) on the network.
- **Message**. One message defines the data bytes transmitted on the CAN bus.
- **Signal**. One message consist of one or more signals.
- **SignalGroup**. Defines a signal group. Seldom in use.
- **Attribute**. All DBC objects may have none or more attributes.  
- **EnvVar**. A Network may define none or more environment variables. Seldom in use.  
- **SignalObserver**. Saves sample values. Used when streaming CAN messages. 
