# CSCI 330 - Semester-Long C++ Project

## Overview

This is an audacious project:  I'm asking you to build a substantial C++ application over the course of the semester using professional software development practices. This project runs parallel to your coursework - you can use whatever C++ features you've learned (or research on your own) at any point. AI is a tool and you can use AI, but you must credit where you use AI and be able to explain every aspect of your code, your development enviornment, and the development process.  

**Duration**: Full semester (15 weeks)  
**Weight**: 30% of course grade (300 points)  
**Philosophy**: This is serious project, so I expect you to build something real, substantial, and portfolio-worthy

> **📚 How to Use These Documents:**  
> - Start here for the complete project overview ("map of the world")
> - Use the individual phase guides (PROJECT_PHASE_1.md through PROJECT_PHASE_5.md) for detailed todo checklists
> - Each phase guide breaks down the work into manageable weekly tasks
> - Check off items as you complete them to track your progress

## Important: Two Parallel Learning Paths

**This project runs parallel to, not in lockstep with, the course chapters.** You're encouraged to use ANY C++ features you need at ANY point - whether from research, AI assistance, or looking ahead in the textbook. 

- **The Chapters** provide deep, systematic understanding of C++ concepts (types, memory models, function mechanics, container internals)
- **The Project** provides real-world context where you use whatever works to solve problems

You might use `std::vector` in Phase 1 before studying Chapter 11 on containers in detail. This is by design and mirrors professional development - you often use tools to solve problems first, then later develop deeper understanding of their internals. The "lightbulb moment" when you formally study something you've already used in your project is valuable learning.

**Bottom line**: Don't wait for permission from the chapters to use a feature. If you need it, research it, use it, and document it. The formal study will come later and deepen your understanding.

## The Five Phases

Each phase has its own detailed guide with todo checklists to keep you on track:

### Phase 1: Planning & Proof of Concept (Weeks 1-3)
**Due**: End of Week 3  
**Points**: 40 (13%)  
**Focus**: Validate your idea works  
📋 **[Detailed Todo List](PROJECT_PHASE_1.md)**

### Phase 2: Minimum Viable Product (Weeks 4-6)  
**Due**: End of Week 6  
**Points**: 60 (20%)  
**Focus**: Core functionality complete  
📋 **[Detailed Todo List](PROJECT_PHASE_2.md)**

### Phase 3: Feature Development (Weeks 7-9)
**Due**: End of Week 9  
**Points**: 70 (23%)  
**Focus**: Add the features that make it interesting  
📋 **[Detailed Todo List](PROJECT_PHASE_3.md)**

### Phase 4: Robustness & Performance (Weeks 10-12)
**Due**: End of Week 12  
**Points**: 70 (23%)  
**Focus**: Make it production-ready  
📋 **[Detailed Todo List](PROJECT_PHASE_4.md)**

### Phase 5: Polish & Presentation (Weeks 13-15)
**Due**: Finals Week  
**Points**: 60 (20%)  
**Focus**: Professional finish and reflection  
📋 **[Detailed Todo List](PROJECT_PHASE_5.md)**

---

## Phase 1: Planning & Proof of Concept

### Goal
Prove your idea is feasible and worth building. Get the hard part working first.

### Deliverables

#### 1.1 Project Proposal (Week 2)
A solid plan that shows you've thought this through:
- **What**: Clear description of what you're building
- **Why**: Problem it solves or need it fills  
- **How**: Technical approach and architecture
- **Risks**: What might go wrong and backup plans
- **Success Criteria**: How we'll know it works

#### 1.2 Proof of Concept (Week 3)
Working code that proves the hardest part is solvable:
- The core algorithm works
- The key technical challenge is solved
- Basic I/O or interface is functional
- Can be ugly, but must work
- Includes simple tests

**Examples**:
- Game project: Basic game loop with player movement
- Database: Store and retrieve records from disk
- Compiler: Parse and evaluate simple expressions
- Network app: Establish connection and exchange messages

#### 1.3 Project Collaboration Hub Participation
- **Share your project idea** in the Project Collaboration Hub discussion for community feedback
- **Post proof-of-concept screenshots** or demos to get early input
- **Help others** troubleshoot their Phase 1 challenges
- **Build connections** with potential peer reviewers

#### Individual Check-In Meeting
**Required**: 15-minute individual meeting with instructor during Week 3
- **Discuss**: Project proposal and proof of concept
- **Review**: Technical feasibility and scope appropriateness  
- **Plan**: Adjustments needed for Phase 2
- **Schedule**: Sign up for meeting slots posted in Canvas

#### Peer Review Requirements
Each phase includes mandatory peer collaboration:
- **Receive feedback from 2 peers** on your deliverables
- **Provide feedback to 2 peers** using structured review forms
- Reviews assigned within 48 hours of submission deadline
- 72-hour window to complete peer reviews

### Grading (40 points)
- Proposal quality and feasibility: 12 pts
- Proof of concept demonstrates core functionality: 12 pts
- Risk assessment realistic: 4 pts
- Initial code quality: 4 pts
- Quality of peer reviews provided: 4 pts
- Incorporation of peer feedback: 4 pts

---

## Phase 2: Minimum Viable Product (MVP)

### Goal
Build the simplest version that could be considered "complete." If you had to ship tomorrow, this would barely work.

### Deliverables

#### Complete Core Functionality
- All essential features working
- Proper class structure and organization
- Memory management handled correctly
- Basic error handling
- Configuration files or settings
- Can be used start-to-finish for basic use case

#### Documentation
- README with build and run instructions
- Basic user guide
- Code comments for complex logic

#### Testing
- Unit tests for core components
- At least one integration test
- No memory leaks (valgrind clean)

#### Project Collaboration Hub Participation
- **Share MVP progress** with screenshots and key functionality demos
- **Ask for architecture feedback** before implementing major features
- **Help others** debug their MVP challenges
- **Celebrate milestones** and encourage classmates

#### Individual Check-In Meeting
**Required**: 15-minute individual meeting with instructor during Week 6
- **Demo**: Core MVP functionality working
- **Discuss**: Architecture decisions and code organization
- **Review**: Progress toward Phase 3 goals
- **Plan**: Feature development priorities

### Grading (60 points)
- Core functionality complete: 20 pts
- Code architecture and organization: 12 pts
- Memory management correct: 8 pts
- Testing adequate: 5 pts
- Documentation exists: 5 pts
- Quality of peer reviews provided: 5 pts
- Incorporation of peer feedback: 5 pts

---

## Phase 3: Feature Development

### Goal
Add the features that make your project interesting and differentiate it from a toy implementation.

### Deliverables

#### Enhanced Functionality
- 3-5 significant features beyond MVP
- Improved user experience
- Performance optimizations where needed
- Advanced C++ features used appropriately (templates, STL, modern C++)

#### Examples of Features to Add
- **Game**: Multiple levels, save/load, achievements, AI opponents
- **Database**: Indexing, transactions, query optimization, joins
- **Tool**: Multiple input formats, batch processing, plugins, scripting
- **Network App**: Authentication, encryption, multiple clients, protocols

#### Quality Improvements
- Comprehensive error handling
- Logging system
- Configuration management
- Better algorithms/data structures

#### Project Collaboration Hub Participation
- **Showcase advanced features** you've implemented
- **Share performance optimization discoveries**
- **Discuss design patterns** and architectural decisions
- **Help others** implement similar advanced features

#### Individual Check-In Meeting
**Required**: 15-minute individual meeting with instructor during Week 9
- **Demo**: New features and advanced functionality
- **Discuss**: C++ features utilized and design patterns applied
- **Review**: Code quality and maintainability
- **Plan**: Robustness and performance optimization strategy

### Grading (70 points)
- Feature implementation quality: 25 pts
- Appropriate use of C++ features: 12 pts
- Performance considerations: 8 pts
- Error handling and robustness: 8 pts
- Code maintainability: 5 pts
- Quality of peer reviews provided: 6 pts
- Incorporation of peer feedback: 6 pts

---

## Phase 4: Robustness & Performance

### Goal
Make it production-ready. Handle edge cases, optimize performance, ensure reliability.

### Deliverables

#### Robustness
- Handles all edge cases gracefully
- Input validation comprehensive
- Recovery from errors
- Stress testing passed
- Security considerations addressed (if applicable)

#### Performance
- Profiling completed
- Bottlenecks identified and addressed
- Memory usage optimized
- Response times acceptable
- Scales to reasonable limits

#### Professional Quality
- Consistent coding style
- Comprehensive test suite (>70% coverage)
- CI/CD pipeline (GitHub Actions)
- Static analysis clean
- Documentation complete

#### Project Collaboration Hub Participation
- **Share debugging and profiling experiences**
- **Post performance benchmarks** and optimization results
- **Discuss production-ready practices** you've implemented
- **Help others** solve robustness and performance challenges

#### Individual Check-In Meeting
**Required**: 15-minute individual meeting with instructor during Week 12
- **Demo**: Production-ready functionality and stress testing
- **Discuss**: Performance optimizations and profiling results
- **Review**: Professional practices and documentation quality
- **Plan**: Final presentation and reflection preparation

### Grading (70 points)
- Robustness and reliability: 16 pts
- Performance optimization: 12 pts
- Test coverage and quality: 12 pts
- Professional practices: 8 pts
- Code quality: 8 pts
- Quality of peer reviews provided: 7 pts
- Incorporation of peer feedback: 7 pts

---

## Phase 5: Polish & Presentation

### Goal
Create a professional finish and reflect on your journey.

### Deliverables

#### 5.1 Final Polish
- User experience refined
- Professional README with screenshots/demos
- Installation guide
- API documentation (if applicable)
- Example use cases or tutorials

#### Project Collaboration Hub Participation
- **Share your final project showcase** with demos and screenshots
- **Reflect on your development journey** in the discussion
- **Help others** prepare for their final presentations
- **Thank classmates** who supported you throughout the semester

#### 5.2 Final Project Presentation (Finals Week)
**Required**: 20-minute individual appointment with instructor

**Live Demo** (7 minutes)
- Show it working end-to-end
- Demonstrate key features
- Show it handling errors gracefully
- Highlight most impressive functionality

**Technical Deep Dive** (10 minutes)
- Architecture overview and evolution across all phases
- Most challenging problems solved and how you solved them
- Sophisticated C++ features utilized and why you chose them
- Performance characteristics and optimization results
- Code walkthrough of your best implementations
- AI collaboration throughout the project

**Q&A and Reflection** (3 minutes)
- Instructor questions about implementation details
- Discussion of what you'd do differently
- Reflection on growth as a C++ developer

#### 5.3 Comprehensive Reflection Paper (3-4 pages)

**Technical Section**
- Architecture decisions and trade-offs
- Algorithms and data structures chosen
- C++ features that were most valuable
- What you'd do differently technically

**Process Section**
- Project management approach
- Time estimation vs. reality
- Biggest surprises
- Most valuable learning moments

**AI Collaboration Analysis** (integrated throughout phases)
- Evolution of AI usage from Phase 1 to Phase 5
- Specific examples of valuable AI assistance
- Times when AI led you astray or provided poor guidance
- What you learned about effective AI collaboration
- Your refined philosophy on AI in professional development
- Documentation of AI usage in each phase deliverable

**Future Work**
- What you'd add with more time
- How you'd refactor or redesign
- Potential real-world applications

### Grading (60 points)
- Final product quality: 20 pts
- Presentation effectiveness: 15 pts
- Reflection paper depth: 15 pts
- Quality of final peer reviews provided: 5 pts
- Overall peer collaboration throughout semester: 5 pts

---

## Project Scope Guidelines

### Expected Complexity by Phase

| Phase | Approximate Lines | Classes/Modules | Features |
|-------|-------------------|------------------|----------|
| 1 | 200-500 | 2-3 | 1 (core) |
| 2 | 500-1000 | 5-8 | 3-4 |
| 3 | 1000-2000 | 10-15 | 7-10 |
| 4 | 1500-2500 | 15-20 | 10-15 |
| 5 | 2000-3000+ | 20+ | All polished |

### Good Project Characteristics
- **Interesting enough** to sustain a semester of work
- **Complex enough** to demonstrate various C++ features
- **Practical enough** that someone might actually use it
- **Scoped appropriately** - challenging but achievable
- **Extensible** - can grow naturally over phases

### Project Categories & Inspiration

#### Systems Programming
Projects that interact closely with the operating system or implement system-level functionality. Think about tools you use daily that could be reimplemented or improved.

#### Games & Simulations
Interactive applications with real-time requirements. Consider both entertainment and educational simulations that model real-world systems.

#### Developer Tools
Software that helps programmers be more productive. What tools do you wish existed for your own development workflow?

#### Data Processing & Analysis
Applications that handle, transform, and analyze data. Consider the data challenges in your field of interest.

#### Network & Distributed Systems
Applications involving multiple computers or network communication. Think about collaboration tools or distributed processing.

#### Computer Graphics & Visualization
Projects that generate visual output or process images. Consider both 2D and 3D applications, or data visualization tools.

#### Language Processing
Compilers, interpreters, or tools that process structured text. Think about domain-specific languages or code analysis tools.

#### Security & Cryptography
Applications focused on data protection, security analysis, or cryptographic implementations.

---

## AI Usage Policy

### Philosophy
Use AI as you would in a professional setting - as a tool to enhance productivity while maintaining ownership and understanding of your code.

### Required Documentation (Integrated into Phase Deliverables)
Each phase submission must include an AI usage section documenting:
- Significant AI interactions during this phase
- Specific prompts used and responses received
- What you implemented vs. what AI suggested
- What you learned from these interactions
- How your AI usage evolved from the previous phase

### Guidelines
- **Always Allowed**: Debugging, syntax help, documentation generation
- **Document When Used**: Algorithm suggestions, design patterns, optimization
- **Not Acceptable**: Having AI write entire features without understanding

### Semester-Long AI Documentation
Track your AI collaboration evolution:
- Phase 1: Learning C++ basics and project planning
- Phase 2: Architecture decisions and implementation help  
- Phase 3: Advanced feature development and optimization
- Phase 4: Debugging, performance tuning, and robustness
- Phase 5: Reflection on the entire AI collaboration experience

---

## Grading Rubric Summary

### Distribution (300 points)
- Phase 1: 40 points (13%) - Planning & Proof of Concept
- Phase 2: 60 points (20%) - MVP
- Phase 3: 70 points (23%) - Feature Development
- Phase 4: 70 points (23%) - Robustness & Performance
- Phase 5: 60 points (20%) - Polish & Presentation

**Note**: Project Discussion collaboration is graded separately as part of the course's Participation & Engagement component.

### Late Policy
- 24 hours: -10%
- 48 hours: -20%
- 72 hours: -30%
- >72 hours: -50%
- Final phase: No late submissions

### Bonus Opportunities (up to 15 points)
- Exceptional innovation: +5
- Outstanding documentation: +3
- Helping classmates (documented): +3
- Extra features beyond requirements: +4

---

## Success Tips

### Start with the Hard Part
Don't build the easy UI first. Solve the core technical challenge in Phase 1.

### Keep It Working
Never break your build for more than a day. Always have a working version.

### Test as You Go
Don't save testing for the end. Write tests with your features.

### Use Version Control Properly
- Commit often with meaningful messages
- Use branches for major features
- Tag each phase submission

### Get Feedback Early
- Show your project to others
- Get user feedback
- Don't work in isolation

### Document Decisions
Keep notes on why you made certain choices - you'll need them for the reflection.

### Use the Project Collaboration Hub
- **Post weekly progress updates** to get community feedback and stay motivated
- **Ask technical questions** when you're stuck - your classmates may have solved similar problems
- **Share breakthroughs and discoveries** - help others learn from your experience  
- **Help others debug** - explaining solutions reinforces your own understanding
- **Build professional relationships** - your classmates today are your network tomorrow

---

## FAQ

**Q: Can I change my project idea after Phase 1?**
A: Yes, but talk to the instructor first. Better to pivot early than fail later.

**Q: What if my Phase 1 proof of concept reveals my idea won't work?**
A: That's valuable! Pivot to your backup plan. Finding out early is the point.

**Q: Can I use external libraries?**
A: Yes! Document them and be able to explain what they do.

**Q: How much should I use AI?**
A: As much as helps you learn and be productive. Document it all.

**Q: What if I'm way ahead/behind schedule?**
A: Talk to the instructor. We can adjust scope or provide extra challenges.

**Q: Can I work on something related to my research/job?**
A: Absolutely! Real projects are the best projects.

---

**Remember**: This is YOUR project. Make something you're proud of, that you'll want to show in job interviews, and that demonstrates your growth as a C++ developer.