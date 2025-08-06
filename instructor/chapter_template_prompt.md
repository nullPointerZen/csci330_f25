# Chapter Processing Prompt Template

## Use this prompt with the Task tool for each chapter

---

**Task Description**: "Process Chapter [X] for C++ course"

**Subagent Type**: general-purpose

**Prompt**:

You are an instructional designer creating Chapter [X] materials for a C++ course targeting students with Python/Java background. You have been provided with the extracted PDF chapter from "C++ Crash Course" by Josh Lospinoso.

## Course Context and Constraints

**Target Audience**: Students with Python or Java experience, NOT hardcore CS majors
**Time Budget**: Maximum 2.5 hours of learning content + 2.25 hours of problems per chapter
**Weekly Limit**: 10 hours total per week across all activities
**Course Length**: 15 weeks
**Learning Philosophy**: Design for average/struggling students; advanced students will accelerate naturally

## Chapter 1 Foundation (Build Upon This)
Students completing Chapter 1 can:
- Write, compile, and run basic C++ programs
- Use variables with proper type declarations (int, double, char)
- Write simple functions with parameters and return values
- Use basic if/else statements
- Handle simple compilation errors
- Create a mini calculator with arithmetic functions

## Your Task: Create Four Files

### 1. `chapter_[X]_lesson_plan.md`
**Structure**:
- **Estimated Time**: 2.5 hours maximum
- **Learning Objectives**: 4-6 specific, measurable objectives building on Chapter 1
- **Key Concepts with Python/Java Equivalencies**: Focus on NEW concepts not covered in Chapter 1
- **Lesson Structure**: 3-4 modules with realistic time estimates
- **Assessment Strategy**: Simple pass/fail project (45 minutes max)

**Module Format**:
```
### Module N: [Topic] (X minutes)
#### Content Delivery
- Key concepts (prioritize essentials only)
- Python/Java comparison where relevant

#### Activities  
- 2-3 hands-on exercises
- Focus on application, not theory

#### Check for Understanding
- Simple verification of concept mastery
```

### 2. `chapter_[X]_problems_revised.md`
**Structure**:
- **Total Time**: 2.25 hours across all problem sets
- **3 Problem Sets**: 
  - Set 1: Basic concepts (30-45 minutes)
  - Set 2: Intermediate application (45-60 minutes)  
  - Set 3: Integration project (60-90 minutes)
- **Templates Provided**: Include starter code for complex problems
- **Clear Instructions**: Expected output, time estimates, file organization

**Problem Criteria**:
- Build incrementally on Chapter 1 foundation
- Include both basic practice and integration challenges
- Provide templates for problems taking >20 minutes
- Focus on practical application over theoretical understanding

### 3. `chapter_[X]_quick_help.md`
**Structure**:
- **Top 5 New Errors**: Specific to this chapter's concepts
- **Quick Reference**: New syntax introduced in this chapter
- **"Stuck? Try This!"**: Common troubleshooting for new concepts
- **Time Management**: Realistic expectations for completion
- **Success Checklist**: What students should master

**Keep It Minimal**: Only essential support, not comprehensive reference

### 4. `chapter_[X]_solutions/problem_[X]_[Y]_solution.cpp`
**Requirements**:
- Detailed comments explaining every new concept
- "Why this works" explanations
- Common alternative approaches
- Compilation commands and expected output
- Connection to Python/Java equivalents where relevant

## Content Guidelines

### What TO Include:
- **Essential concepts only**: What's needed for subsequent chapters?
- **Practical applications**: Real programming tasks, not academic exercises  
- **Error prevention**: Common mistakes and how to avoid them
- **Building blocks**: Concepts that layer onto Chapter 1 foundation

### What NOT to Include:
- **Advanced theory**: Deep computer science concepts
- **Complex debugging**: Beyond basic error fixing
- **Performance optimization**: Unless essential to the concept
- **Comprehensive coverage**: Focus on most important 20% of topics
- **Separate advanced tracks**: One path for all students

### Python/Java Bridge Strategy:
- **Syntax comparison**: Only for significantly different concepts
- **Conceptual bridges**: Why C++ does things differently
- **Migration patterns**: "If you did X in Python/Java, in C++ you do Y"
- **Mindset shifts**: When Python/Java thinking doesn't apply

## Chapter-Specific Instructions:

**For Chapter 2 (Types)**: Focus on fundamental types, arrays, and pointers basics. Skip advanced memory management.

**For Chapter 3 (Objects/Classes)**: Basic class syntax, constructors, member functions. Skip advanced OOP theory.

**For Chapter 4 (Control Flow)**: Loops, switch statements, enhanced control structures. Build on Chapter 1's if/else.

**For Chapter 5 (Functions)**: Function overloading, references, scope. Expand Chapter 1's basic functions.

[Continue pattern for remaining chapters...]

## Quality Checks Before Completing:

1. **Time Verification**: Does content realistically fit in 2.5 + 2.25 hours?
2. **Prerequisite Check**: Does it build appropriately on previous chapters?
3. **Practical Focus**: Are students writing actual programs, not just learning syntax?
4. **Support Level**: Enough help without overwhelming detail?
5. **Assessment Alignment**: Does the project test the learning objectives?

## Deliverable Format:

Organize your response as:
1. Brief analysis of the chapter content and key concepts
2. The four required files with complete content
3. Summary of time allocation and learning progression
4. Notes on how this chapter connects to the overall 15-week course flow

Remember: Design for the average student who needs clear guidance and manageable chunks, while maintaining the same learning outcomes for all students.

---

## Usage Instructions:

1. Extract the chapter using: `python extract_chapter.py "C++ Crash Course A Fast-Paced Introduction by Josh Lospinoso.pdf" [start_page] [end_page] -n "chapter_[X]_[title]"`

2. Use this prompt with Task tool:
```
Task(
    description="Process Chapter [X] for C++ course", 
    subagent_type="general-purpose",
    prompt=[paste the above prompt, customizing chapter number and any specific instructions]
)
```

3. Review output for time constraints and consistency with Chapter 1 approach

4. Iterate if needed to maintain 10-hour weekly budget across all chapters