# 🏭 Warehouse Inventory Management Order Processing System

## Overview

This project simulates a real-time warehouse order processing system using Linux concepts like processes, threads, IPC, and signals.

---

## Features

* `fork()` for process creation
* Pipe (Generator → Processor)
* FIFO (Processor → Logger)
* `pthread` (multithreading)
* Mutex for synchronization
* Signal handling (`SIGINT`)

---

## Flow

Generator → PIPE → Processor → FIFO → Logger → Log File

---

## Compile and Run (Using Makefile)

This project uses a Makefile for easy compilation.

```
make
./warehouse
```

### Clean build files

---
make clean
---

## Architecture Diagram

<img width="1115" height="762" alt="warehouse_architecture" src="https://github.com/user-attachments/assets/b28ceda0-e5cd-44d3-b762-07b67098492b" />

## Output

Logs are stored in `store_order.log`



