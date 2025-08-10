# CSCI 330 - Project Brainstorming Guide

## What Makes a Good Semester Project?

Your project should be:
- **Substantial**: 2000-3000+ lines by the end, starting from 200-500
- **Interesting**: Something you're excited to work on for 15 weeks
- **Practical**: Solves a real problem or provides entertainment
- **Portfolio-worthy**: You'd be proud to show this in interviews

## Project Ideas by Category

### Games & Entertainment

#### Snake with AI Opponent
- **Phase 1 Core**: Basic snake movement, collision detection, food spawning
- **Growth Path**: AI pathfinding opponent, power-ups, obstacles, maze generation
- **Technical Skills**: Game loops, collision algorithms, pathfinding (A*)
- **Why It Works**: Classic game everyone knows, natural complexity progression

#### Text-Based RPG Engine
- **Phase 1 Core**: Combat system with player/enemy stats and turn-based battles
- **Growth Path**: Inventory system, quest tracking, save/load, dialogue trees
- **Technical Skills**: State machines, file I/O, object hierarchies
- **Why It Works**: Highly extensible, great for OOP design patterns

#### Tower Defense Framework
- **Phase 1 Core**: Enemy waves following path, one tower type that shoots
- **Growth Path**: Multiple towers, upgrades, economy, different enemy types
- **Technical Skills**: Pathfinding, collision detection, resource management
- **Why It Works**: Combines real-time action with strategic elements

#### Math Puzzle Generator
- **Phase 1 Core**: Generate valid Sudoku puzzles with one difficulty
- **Growth Path**: Solver algorithm, multiple difficulties, hint system, other puzzle types
- **Technical Skills**: Constraint satisfaction, backtracking algorithms
- **Why It Works**: Clear rules, algorithmic challenge, practical output

### Developer Tools

#### Static Code Analyzer
- **Phase 1 Core**: Parse C++ files and count functions/classes
- **Growth Path**: Complexity metrics, style checking, dependency graphs
- **Technical Skills**: Parsing, AST manipulation, pattern matching

#### Build System Tool
- **Phase 1 Core**: Dependency tracking and basic compilation
- **Growth Path**: Parallel builds, caching, cross-platform support
- **Technical Skills**: Graph algorithms, process management, file watching

#### Documentation Generator
- **Phase 1 Core**: Extract comments and generate basic HTML
- **Growth Path**: Markdown support, cross-references, search functionality
- **Technical Skills**: Text parsing, template engines, static site generation

### Systems Programming

#### Custom Shell
- **Phase 1 Core**: Execute commands and handle basic piping
- **Growth Path**: Job control, scripting, aliases, history
- **Technical Skills**: Process management, signal handling, parsing

#### Memory Pool Allocator
- **Phase 1 Core**: Fixed-size block allocation
- **Growth Path**: Variable sizes, thread safety, debugging features
- **Technical Skills**: Memory management, performance optimization

#### File System Utilities
- **Phase 1 Core**: Recursive directory traversal and basic operations
- **Growth Path**: Search patterns, compression, synchronization
- **Technical Skills**: File I/O, tree algorithms, system calls

### Data & Analytics

#### Time-Series Database
- **Phase 1 Core**: Store and retrieve timestamped data
- **Growth Path**: Indexing, aggregations, compression, queries
- **Technical Skills**: B-trees, data structures, query optimization

#### CSV Processing Engine
- **Phase 1 Core**: Parse and filter CSV files
- **Growth Path**: Joins, aggregations, SQL-like queries, large file handling
- **Technical Skills**: Stream processing, memory efficiency, parsing

#### Data Visualization Tool
- **Phase 1 Core**: Generate basic charts from data files
- **Growth Path**: Interactive charts, real-time updates, multiple formats
- **Technical Skills**: Graphics programming, data transformation

### Network Applications

#### Chat Application
- **Phase 1 Core**: Client-server message exchange
- **Growth Path**: Multiple rooms, encryption, file sharing, history
- **Technical Skills**: Socket programming, protocols, concurrency

#### HTTP Server
- **Phase 1 Core**: Serve static files with GET requests
- **Growth Path**: Dynamic content, caching, compression, HTTPS
- **Technical Skills**: Network protocols, concurrent connections

#### P2P File Sharing
- **Phase 1 Core**: Direct file transfer between two peers
- **Growth Path**: Discovery, chunking, multiple peers, integrity checks
- **Technical Skills**: Distributed systems, protocols, networking

## Reality Check: Scope for 15 Weeks

### Phase Progression Guidelines

| Phase | Week | Lines of Code | What You Should Have |
|-------|------|--------------|---------------------|
| 1 | 3 | 200-500 | Core algorithm working |
| 2 | 6 | 500-1000 | Basic complete system |
| 3 | 9 | 1000-2000 | Key features added |
| 4 | 12 | 1500-2500 | Robust and optimized |
| 5 | 15 | 2000-3000+ | Polished and documented |

### Warning Signs Your Scope is Too Big
- Needs multiple complex algorithms to work at all
- Requires extensive external libraries just to start
- "It's like Facebook but..."
- Can't explain it in one sentence

### Signs Your Scope is Too Small
- Could be done in a weekend
- No room for interesting features
- Single algorithm with no system around it
- No clear path to grow complexity

## Getting Started

### Step 1: Pick Your Interest Area
Choose based on what excites you:
- Love games? Pick a game project
- Into systems? Build a tool or utility  
- Data person? Create an analytics engine
- Network curious? Build a distributed app

### Step 2: Identify Your Phase 1 Core
What's the ONE thing that must work for your project to exist?
- For a game: Core gameplay loop
- For a database: Store and retrieve
- For a network app: Connect and communicate
- For a tool: Basic primary function

### Step 3: Plan Your Growth
How will you expand across phases?
- What features are "nice to have" vs. essential?
- What can you add if you're ahead of schedule?
- What can you cut if you fall behind?

## Final Checklist

Before committing to your project:

✓ Can you build a proof of concept in 200-500 lines?  
✓ Do you have 5-10 features to add over the semester?  
✓ Will you learn new C++ concepts building this?  
✓ Would you demo this in a job interview?  
✓ Are you excited to work on this for 15 weeks?

---

**Remember**: The best project is one that challenges you while being achievable. Pick something you'll enjoy building and be proud to have built!