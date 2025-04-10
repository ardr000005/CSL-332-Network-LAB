# 🧠 CSL-332 Network Lab Programs

This repository contains implementations of various **computer network protocols** and **simulations** for the CSL-332 Networking Laboratory.

Each protocol is implemented in **C** using socket programming, and simulations are done using **NS2 (Network Simulator 2)** with **TCL scripts**.

---

## 📁 Folder Structure

```
.
├── DVR/          # Distance Vector Routing
│   └── dvr.c
│
├── FTP/          # File Transfer Protocol
│   ├── ftp_client.c
│   ├── ftp_server.c
│   └── hello.txt
│
├── GBC/          # Go-Back-N ARQ
│   ├── gbc_client.c
│   └── gbc_server.c
│
├── LK/           # Leaky Bucket Algorithm
│   └── lk.c
│
├── NS2/          # NS2 Network Simulation
│   └── simulation.tcl
│
├── S_Window/     # Sliding Window Protocol (Common area)
│
├── SR/           # Selective Repeat ARQ
│   ├── sr_client.c
│   └── sr_server.c
│
├── stop_wait/    # Stop-and-Wait ARQ
│   ├── sw_receiver.c
│   └── sw_sender.c
│
├── TCP/          # TCP Client-Server
│   ├── tcp_client.c
│   └── tcp_server.c
│
└── UDP/          # UDP Client-Server
    ├── udp_client.c
    └── udp_server.c
```

---

## 🧪 Lab Programs

| Protocol / Concept        | Description                         |
|---------------------------|-------------------------------------|
| **TCP**                   | Client-Server communication using TCP |
| **UDP**                   | Client-Server communication using UDP |
| **FTP**                   | File transfer via socket programming |
| **Stop-and-Wait ARQ**     | Simple ARQ protocol (sender/receiver) |
| **Go-Back-N ARQ**         | ARQ with window size and retransmission |
| **Selective Repeat ARQ**  | Efficient ARQ with selective acknowledgment |
| **Leaky Bucket**          | Traffic shaping algorithm |
| **Distance Vector Routing** | Simulates DVR routing logic |
| **NS2 Simulation**        | Network topology simulation using TCL |

---

## 🚀 How to Run (for C programs)

1. Compile the programs:

```bash
gcc tcp_server.c
gcc tcp_client.c
```

2. In two terminals:
```bash
./server
./client
```

(Replace filenames as needed for each protocol.)

---

## 🎯 NS2 Simulation

1. Make sure NS2 is installed.
2. Run the simulation script:

```bash
ns simulation.tcl
```

3. View the output:

```bash
nam out.nam
```

---

## 🙌 Author

- **GitHub**: [ardr000005](https://github.com/ardr000005)
- All programs written in C or TCL under Ubuntu Linux.

---

## 📝 License

This lab work is shared for educational purposes.  
This project is licensed under the [MIT License](./LICENSE).


