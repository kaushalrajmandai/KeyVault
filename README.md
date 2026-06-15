# KeyVault — Digital Intellectual Asset Registry

> **ITM Skills University | B.Tech CSE 2025-29 | Semester II Sprint 2 Examination**
> Course: Data Structures & Algorithms with C++
> Case Study 3: Digital Intellectual Asset Registry

---

## Project Title

**KeyVault** — A Digital Intellectual Asset Registry System for Online Software License Marketplaces

---

## Problem Statement

KeyVault is an online marketplace for selling software licenses, similar to platforms that distribute antivirus keys or game activation codes. With millions of licenses from thousands of publishers, the system faces critical performance issues:

- Searching for a license by typing the first few characters is painfully slow
- When an admin accidentally revokes a user's access rights, there is no way to undo it instantly
- License update requests from around the world pile up but get processed in random order, causing unfair wait times
- Verifying whether a specific license key is genuine takes too long because the system checks every record one by one
- There is no clear picture of how licenses flow from creators to publishers to end users, making it impossible to audit royalty payments or detect piracy rings

---

## Objectives

1. Implement a **Trie** for ultra-fast prefix-based license title search
2. Implement a **Stack** to maintain permission change history with instant undo capability
3. Implement a **Queue (FIFO)** to ensure fair, ordered processing of license update requests
4. Implement a **Hash Map** for O(1) license key verification
5. Implement **Merge Sort** to rank digital assets by market value or usage frequency
6. Implement a **Graph (Adjacency List)** to model the creator → publisher → user distribution network
7. Implement **BFS** to find the shortest license verification path
8. Implement a **Greedy Algorithm** (Fractional Knapsack) to optimize corporate bundle purchases

---

## System Overview

```
KeyVault System
│
├── Copyright Directory  ──► Trie               (Feature 1)
├── History Tracker      ──► Stack               (Feature 2)
├── Update Line          ──► Queue (FIFO)         (Feature 3)
├── Key Lookup           ──► Hash Map             (Feature 4)
├── Value Sorter         ──► Merge Sort           (Feature 5)
├── License Network      ──► Graph (Adj. List)    (Feature 6)
├── Quick Check          ──► BFS Shortest Path    (Feature 7)
└── Discount Planner     ──► Greedy Algorithm     (Feature 8)
```

---

## Data Structures and Algorithms Used

| Feature | Data Structure / Algorithm | Time Complexity | Real-world Analogy |
|---|---|---|---|
| Copyright Directory | Trie | O(L) search | Steam search bar |
| History Tracker | Stack (LIFO) | O(1) push/pop | Ctrl+Z in admin panel |
| Update Line | Queue (FIFO) | O(1) enqueue/dequeue | License activation queue |
| Key Lookup | Hash Map | O(1) average | Windows product key check |
| Value Sorter | Merge Sort | O(n log n) | Top Sellers chart |
| License Network | Directed Graph (Adj. List) | O(V+E) traversal | Royalty flow tracking |
| Quick Check | BFS on Graph | O(V+E) | CDN nearest server routing |
| Discount Planner | Greedy (Fractional Knapsack) | O(n log n) | Volume licensing optimizer |

---

## Execution Steps

### Prerequisites
- C++17 compatible compiler (g++ recommended)
- Linux / macOS terminal or Windows with MinGW

### Compile and Run
```bash
g++ -std=c++17 keyvault.cpp -o keyvault
./keyvault
```

### Menu
```
1. Copyright Directory   (Trie)
2. History Tracker       (Stack)
3. Update Line           (Queue)
4. Key Lookup            (Hash Map)
5. Value Sorter          (Merge Sort)
6. License Network       (Graph)
7. Quick Check           (BFS)
8. Discount Planner      (Greedy)
9. Run All
0. Exit
```

Enter `9` to run all 8 features at once.

---

## Complexity Analysis

| Module | Operation | Time | Space |
|---|---|---|---|
| Trie | Insert | O(L) | O(L x alphabet) |
| Trie | Prefix Search | O(P + W) | O(1) extra |
| Stack | Push / Pop | O(1) | O(n) |
| Queue | Enqueue / Dequeue | O(1) | O(n) |
| Hash Map | Insert / Lookup | O(1) avg | O(n) |
| Merge Sort | Sort | O(n log n) | O(n) |
| Graph BFS | Traversal | O(V + E) | O(V) |
| BFS Shortest Path | Pathfinding | O(V + E) | O(V) |
| Greedy | Sort + Select | O(n log n) | O(1) extra |

---

## Student Details

| Field | Details |
|---|---|
| Student Name | Kaushal Rajmandai |
| Roll Number | 150096725111 |
| Programme | B.Tech CSE 2025-29 |
| Semester | Semester II Sprint 2 Examination |
| Subject | Data Structures & Algorithms with C++ |
| Case Study | 3 — Digital Intellectual Asset Registry |
| University | ITM Skills University, Navi Mumbai |

---

## GitHub Repository

**https://github.com/kaushalrajmandai/KeyVault**
