# ITCH 5.0 Parser & Limit Order Book

A C++23 project focused on implementing a low-copy NASDAQ ITCH 5.0 market data parser and an efficient limit order book with a modular matching engine.

**Status:** Work in progress. The limit order book and initial Price-Time Priority matching implementation are in place. The ITCH 5.0 parser is still under development.

## Overview

The project aims to build a system capable of processing market data messages and maintaining an order book that reflects the current state of a financial instrument's market.

The implementation is divided into two main components:

- **ITCH 5.0 Parser:** Responsible for decoding incoming ITCH 5.0 messages and translating them into events that can be processed by the order book.
- **Limit Order Book & Matching Engine:** Responsible for maintaining buy and sell orders, handling order modifications and cancellations, and matching incoming orders according to a configurable matching strategy.

## Current Features

### Limit Order Book

The order book maintains separate buy and sell sides, organized by price levels.

Implemented functionality:

- Insert buy and sell limit orders.
- Cancel existing orders using their order ID.
- Modify order price and quantity.
- Retrieve the best bid and best ask.
- Retrieve the best bid and ask price levels.
- Query aggregated quantity at a given price level.
- Display the current order book in a formatted terminal output.

### Data Structures

The current implementation uses:

| Data structure | Purpose |
|---|---|
| `std::map` | Maintains price levels in sorted order. |
| `std::list` | Stores orders within each price level, preserving FIFO order. |
| `std::unordered_map` | Provides direct lookup of orders by ID. |

The buy and sell sides use different map comparators:

- **Bids:** `std::greater<Price>` — highest price first.
- **Asks:** `std::less<Price>` — lowest price first.

This allows constant-time access to the best price level through `begin()`, while maintaining efficient insertion and removal of price levels.

### Matching Engine

The matching engine processes incoming orders and attempts to execute them against orders on the opposite side of the book.

The current architecture separates the matching process from the allocation algorithm using a strategy-based design.

Implemented matching functionality:

- Check whether incoming and resting orders have compatible prices.
- Retrieve the best opposing price level.
- Allocate execution quantities according to a matching strategy.
- Handle partial fills.
- Remove completely filled resting orders.
- Insert any remaining quantity into the order book.

### Matching Strategies

Matching algorithms implement a common `MatchingStrategy` interface, allowing the matching engine to use different allocation policies without changing its core matching workflow.

**Currently implemented:**

- **Price-Time Priority (FIFO):** Orders at better prices receive priority. At the same price level, older orders are matched first.

**Planned:**

- **Pro-Rata:** Distribute execution quantities proportionally among orders at the same price level.

## Project Structure

```text
.
├── include/
│   ├── Order.hpp
│   ├── PriceLevel.hpp
│   ├── LimitOrderBook.hpp
│   ├── MatchingEngine.hpp
│   ├── MatchingStrategy.hpp
│   ├── PriceTimeStrategy.hpp
│   └── Parser.hpp
│
├── src/
│   ├── LimitOrderBook.cpp
│   ├── MatchingEngine.cpp
│   ├── PriceTimeStrategy.cpp
│   ├── Parser.cpp
│   └── main.cpp
│
└── CMakeLists.txt
```

## Building

### Requirements

- C++23 compatible compiler.
- CMake 3.14 or newer.

### Compile

Clone the repository:

```bash
git clone https://github.com/RaduGhenea/ITCH-5.0-no-copy-parser-and-Order-Book.git

cd ITCH-5.0-no-copy-parser-and-Order-Book
```

Configure the project:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

Run:

```bash
./build/orderbook
```

## Development Roadmap

The project is actively being developed. The main planned additions are:

### ITCH 5.0 Parser
- Implement decoding of ITCH 5.0 message types.
- Develop the message dispatch mechanism.
- Process order-related messages and translate them into order book operations.
- Integrate the parser with the order book.

### Matching Engine
- Implement additional matching algorithms, starting with Pro-Rata.
- Introduce trade execution records.
- Extend the matching strategy interface to support different allocation rules.

### Testing & Performance
- Add automated unit tests for order book operations.
- Test matching behavior, partial fills and order priority.
- Benchmark the order book and matching engine.
- Investigate performance improvements and alternative data structures.

## Disclaimer

This is an educational and experimental project intended to explore market microstructure, order book data structures, matching algorithms and efficient C++ design.

It is not intended for use in production trading systems.
