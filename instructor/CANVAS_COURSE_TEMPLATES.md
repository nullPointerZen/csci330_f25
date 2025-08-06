# Canvas Course Templates - C++ Course

## 🎯 Ready-to-Import Course Templates

These templates provide complete Canvas course configurations that instructors can import and customize. Each template is optimized for different teaching contexts.

---

## 📋 Template Overview

### **Template 1: Traditional Semester Course** 
- **Duration**: 15 weeks
- **Structure**: Weekly modules with due dates
- **Assessment**: Traditional grading with letter grades
- **Best for**: Standard university semester courses

### **Template 2: Competency-Based Course**
- **Duration**: Flexible (8-16 weeks)
- **Structure**: Outcome-based with mastery requirements
- **Assessment**: Learning mastery without traditional grades
- **Best for**: Skills-focused programs, competency-based education

### **Template 3: Self-Paced Online Course**
- **Duration**: Self-paced (suggested 15 weeks)
- **Structure**: Open access modules, no due dates
- **Assessment**: Flexible deadlines, multiple attempts
- **Best for**: Online education, adult learners, professional development

---

## 🏫 Template 1: Traditional Semester Course

### **Course Configuration**

#### **Basic Settings**
```
Course Name: C++ Programming for Python/Java Programmers
Course Code: CS XXX
Credit Hours: 3
Grading Scheme: Letter Grades (A, B, C, D, F)
Time Zone: [Institution Time Zone]
Course Format: On-Campus/Blended
```

#### **Navigation Settings**
```
Navigation Items:
✅ Home
✅ Modules  
✅ Assignments
✅ Discussions
✅ Grades
✅ Files
✅ Syllabus
❌ Quizzes (integrated into modules)
❌ People (optional)
❌ Pages (content in modules)
```

### **Module Structure (16 Modules)**

#### **Module 0: Course Setup (Week 1, Days 1-2)**
```
📁 Module 0: Course Setup & Environment
├── 📄 Welcome Video & Course Overview (Canvas Page)
├── 📄 Syllabus (Canvas Syllabus tool)
├── 📄 Development Environment Setup
│   └── External URL: DEVELOPMENT_SETUP.md
├── 📄 Student Guide
│   └── External URL: STUDENT_GUIDE.md
├── ✅ Environment Verification Quiz
│   ├── Type: Graded Quiz (10 points)
│   ├── Questions: 5 multiple choice about setup completion
│   ├── Attempts: Unlimited
│   └── Due: Week 1, Wednesday
├── 💬 Introduction Discussion
│   ├── Prompt: "Introduce yourself and share your Python/Java background"
│   ├── Points: 5 points participation
│   └── Due: Week 1, Friday
└── Prerequisites: None
```

#### **Module 1: Up and Running (Week 1, Days 3-5)**
```
📁 Module 1: Up and Running
├── 📄 Chapter 1: Complete Guide
│   └── External URL: chapter_01_complete.md
├── 💻 Assignment: Problem Set 1 - First Steps
│   ├── Instructions: Complete problems 1.1-1.3 from Chapter 1
│   ├── Submission: File upload (.cpp files) + Text reflection
│   ├── Points: 30 points
│   ├── Rubric: Competency-based (D=18, P=24, A=30)
│   └── Due: Week 2, Monday
├── 💻 Assignment: Problem Set 2 - Variables and Types  
│   ├── Instructions: Complete problems 2.1-2.3 from Chapter 1
│   ├── Points: 30 points
│   └── Due: Week 2, Wednesday
├── 💻 Assignment: Problem Set 3 - Control Flow
│   ├── Instructions: Complete problems 3.1-3.3 from Chapter 1
│   ├── Points: 30 points
│   └── Due: Week 2, Friday
├── ✅ Chapter 1 Success Checklist
│   ├── Type: Practice Quiz (ungraded)
│   ├── Attempts: Unlimited
│   └── Purpose: Self-assessment before Module 2
├── 💬 Discussion: C++ vs Python/Java
│   ├── Prompt: "What surprised you most about C++ compared to Python/Java?"
│   ├── Points: 5 points
│   └── Due: Week 2, Friday
└── Prerequisites: Complete Module 0
```

#### **Modules 2-14: Chapter Modules (Weeks 2-14)**
```
[Pattern repeats for each chapter with:]
├── 📄 Chapter Content (External URL to chapter_XX_complete.md)
├── 💻 Problem Set 1 (30 points, Due: Monday)
├── 💻 Problem Set 2 (30 points, Due: Wednesday) 
├── 💻 Problem Set 3 (30 points, Due: Friday)
├── ✅ Success Checklist (Practice Quiz, ungraded)
├── 💬 Chapter Discussion (5 points, Due: Friday)
└── Prerequisites: Complete previous module + success checklist
```

#### **Module 15: Portfolio & Final Assessment (Week 15)**
```
📁 Module 15: Portfolio & Final Assessment
├── 📄 Competency Assessment Guide
│   └── External URL: COMPETENCY_ASSESSMENT.md
├── 📄 Course Progress Summary
│   └── External URL: COURSE_PROGRESS.md
├── 💻 Portfolio Submission
│   ├── Instructions: Submit 3 best projects + reflection essay
│   ├── Points: 200 points
│   ├── Submission: File upload + URL to GitHub repository
│   └── Due: Week 15, Wednesday
├── 📊 Final Competency Demonstration
│   ├── Type: Conference/Individual meeting
│   ├── Duration: 15 minutes per student
│   ├── Points: 100 points
│   └── Schedule: Week 15
└── Prerequisites: Complete Modules 1-14
```

### **Assignment Groups & Grading**
```
Assignment Groups:
├── Problem Sets: 70% (126 assignments × 30 points = 3,780 points)
├── Environment & Setup: 5% (15 points)
├── Discussions: 5% (75 points)
├── Portfolio: 15% (200 points)
└── Final Demonstration: 5% (100 points)

Total Points: 4,170 points

Grading Scale:
├── A: 93-100% (3,878+ points)
├── A-: 90-92% (3,753+ points)  
├── B+: 87-89% (3,628+ points)
├── B: 83-86% (3,461+ points)
├── B-: 80-82% (3,336+ points)
├── C+: 77-79% (3,211+ points)
├── C: 73-76% (3,044+ points)
├── C-: 70-72% (2,919+ points)
├── D: 60-69% (2,502+ points)
└── F: <60% (<2,502 points)
```

---

## 🎓 Template 2: Competency-Based Course

### **Course Configuration**

#### **Basic Settings**
```
Course Name: C++ Programming - Competency Based
Course Code: CS XXX
Learning Mastery: Enabled
Grading Scheme: Learning Mastery (No letter grades)
Duration: Flexible (8-16 week suggested range)
Course Format: Competency-Based
```

#### **Learning Outcomes Setup**
```
Learning Outcome 1: Development Environment Mastery
├── Description: Can set up, configure, and use professional C++ tools
├── Mastery Points: 3 (Developing=1, Proficient=2, Advanced=3)
├── Aligned Items: Setup quiz, all debugging assignments
└── Evidence: Portfolio + practical demonstration

Learning Outcome 2: Memory Management Understanding
├── Description: Can work with C++ memory safely and effectively
├── Mastery Points: 3
├── Aligned Items: Chapters 2, 4, 11 assignments
└── Evidence: Memory management project + code review

Learning Outcome 3: Object-Oriented Programming
├── Description: Can design classes with proper lifecycle management
├── Mastery Points: 3
├── Aligned Items: Chapters 3, 4, 5 assignments
└── Evidence: OOP system project

Learning Outcome 4: Modern C++ Usage
├── Description: Can use contemporary C++ features effectively
├── Mastery Points: 3
├── Aligned Items: Chapters 9, 11, 12, 13, 14 assignments
└── Evidence: Modern C++ application

Learning Outcome 5: Problem Solving & Debugging
├── Description: Can systematically identify and fix problems
├── Mastery Points: 3
├── Aligned Items: All problem sets, debugging exercises
└── Evidence: Debugging methodology demonstration

Learning Outcome 6: Professional Development Practices
├── Description: Can work like a professional C++ developer
├── Mastery Points: 3
├── Aligned Items: GitHub submissions, code reviews, portfolio
└── Evidence: Professional portfolio + peer reviews
```

### **Module Structure (Flexible Access)**
```
📁 All Modules Available Immediately
├── Prerequisites: None (self-managed progression)
├── Mastery Gates: Must demonstrate competency to complete course
├── Support: Individual coaching, peer mentoring
└── Timeline: Suggested 15-week pace, flexible completion
```

### **Assessment Structure**
```
Competency Demonstrations:
├── Practical Coding Sessions: 40%
│   └── Individual 15-minute sessions showing working code
├── Code Portfolio Reviews: 25%
│   └── GitHub repository with documented projects
├── Problem Solving Challenges: 25%
│   └── Novel problems requiring integration of concepts
└── Peer Teaching/Mentoring: 10%
    └── Help other students, demonstrate mastery

Mastery Requirements:
├── Course Completion: All outcomes at Proficient (2) level
├── Honors Completion: 4+ outcomes at Advanced (3) level
└── Remediation: Additional support for Developing (1) level
```

---

## 🌐 Template 3: Self-Paced Online Course

### **Course Configuration**

#### **Basic Settings**
```
Course Name: C++ Programming - Self-Paced Online
Course Code: CS XXX  
Course Format: Online/Asynchronous
Duration: Open enrollment, suggested 15 weeks
Grading Scheme: Complete/Incomplete or Letter Grades
Time Zone: Multiple (global accessibility)
```

#### **Flexibility Settings**
```
Assignment Settings:
├── Due Dates: None (suggested timelines provided)
├── Late Policy: No penalties (self-managed pacing)
├── Multiple Attempts: Unlimited for all assignments
├── Time Limits: None on quizzes
└── Prerequisites: Relaxed (advisory only)

Support Structure:
├── Discussion Boards: Asynchronous peer support
├── Virtual Office Hours: Optional weekly sessions
├── Help Documentation: Comprehensive FAQ and guides
└── Progress Tracking: Self-assessment + Canvas analytics
```

### **Module Structure (Open Access)**
```
📁 All 16 Modules Available Immediately
├── Suggested Pace: 1 module per week for 15 weeks
├── Prerequisites: Advisory recommendations only
├── Progress Indicators: Visual progress bars and checklists
└── Support Resources: Help documents and peer forums

Module Content (Same as Template 1):
├── Chapter content links
├── Problem sets (unlimited attempts)
├── Self-assessment quizzes
├── Asynchronous discussions
└── Portfolio building guidance
```

### **Assessment Adaptations**
```
Flexible Assessment Options:
├── Problem Sets: Multiple attempts, peer review optional
├── Success Checklists: Self-paced, formative feedback
├── Discussions: Asynchronous, ongoing participation
├── Portfolio: Rolling submissions, iterative improvement
└── Final Assessment: Scheduled when student ready

Grading Options:
Option A - Complete/Incomplete:
├── Complete: Satisfactory completion of all competency areas
└── Incomplete: Additional work needed, no time penalty

Option B - Traditional Grades:
├── Same scale as Template 1
├── No late penalties
└── Grade improvement through resubmissions
```

---

## 🔧 Implementation Instructions

### **Canvas Import Process**

#### **Step 1: Choose Template**
1. Download appropriate template configuration file
2. Access Canvas course creation
3. Select "Import Existing Content"
4. Choose "Canvas Course Export Package"

#### **Step 2: Customize for Institution**
```
Required Customizations:
├── Course name and code
├── Institution-specific information
├── Due dates (Templates 1 & 2)
├── Point values (if different scale needed)
└── Navigation preferences
```

#### **Step 3: Content Integration**
```
Option A - Upload Files:
1. Upload all .md files to Canvas Files
2. Update module links to Canvas file URLs
3. Test all links and downloads

Option B - External Links:
1. Host files on institutional server or GitHub
2. Update module links to external URLs  
3. Test accessibility and permissions

Option C - Canvas Pages:
1. Convert key content to Canvas Pages
2. Maintain external links for detailed content
3. Optimize for mobile viewing
```

### **Post-Import Configuration**

#### **Student Communication Setup**
```
Announcements:
├── Welcome message with course overview
├── Week 1: Environment setup support
├── Week 8: Midterm progress check
└── Week 15: Final portfolio guidelines

Email Templates:
├── Welcome email with setup instructions
├── Weekly progress check-ins (optional)
├── Overdue assignment reminders
└── Portfolio submission guidelines
```

#### **Integration Testing Checklist**
```
✅ All module links work correctly
✅ Assignment submissions function properly  
✅ Rubrics align with competency levels
✅ Discussion prompts are engaging
✅ Mobile accessibility tested
✅ Student view navigation verified
✅ Gradebook calculations correct
✅ Analytics tracking operational
```

---

## 📊 Template Comparison Matrix

| Feature | Traditional Semester | Competency-Based | Self-Paced Online |
|---------|---------------------|------------------|------------------|
| **Duration** | 15 weeks fixed | 8-16 weeks flexible | Unlimited |
| **Due Dates** | Weekly deadlines | Flexible milestones | Suggested only |
| **Grading** | Letter grades | Mastery levels | Complete/Incomplete or Grades |
| **Prerequisites** | Sequential modules | Competency gates | Advisory only |
| **Support** | Scheduled office hours | Individual coaching | Asynchronous help |
| **Assessment** | Traditional assignments | Competency demonstrations | Flexible options |
| **Best For** | University courses | Skills programs | Professional development |

---

## 🎯 Success Metrics by Template

### **Traditional Semester Course**
- **Completion Rate**: >85% student completion
- **Grade Distribution**: Normal curve with majority B/C grades
- **Engagement**: Regular assignment submission, discussion participation
- **Time to Competency**: 15 weeks for most students

### **Competency-Based Course**  
- **Mastery Achievement**: >90% reach Proficient level in all outcomes
- **Time Variance**: Students complete in 8-20 weeks based on background
- **Depth of Learning**: Higher retention and transfer of skills
- **Professional Readiness**: Direct mapping to industry competencies

### **Self-Paced Online Course**
- **Flexibility Success**: Students complete at optimal personal pace
- **Geographic Reach**: Global accessibility without time zone constraints
- **Adult Learner Success**: Higher completion rates for working professionals
- **Resource Efficiency**: Scalable to large enrollments

---

**These Canvas course templates provide complete, ready-to-implement configurations that preserve the simplified C++ course structure while leveraging Canvas LMS capabilities.** 🎯

Each template is optimized for its target context while maintaining the educational improvements achieved through the course simplification process.

---

*These Canvas course templates complement the simplified C++ course materials, providing complete Learning Management System implementations for different educational contexts.*