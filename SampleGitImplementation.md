Here's a comprehensive prompt for implementing the same Git
  workflow in other courses (note: this was written from the perspective of CSCI347_f25):

  # Course Git Workflow Implementation Prompt

  I need you to implement a professional Git workflow for my
  course that uses Pull Request submissions like industry
  development practices. Here are the requirements:

  ## Core Git Workflow Requirements

  ### 1. Student Repository Structure
  Students should:
  - Fork the main course repository to their personal GitHub
  account
  - Work in feature branches (never directly in main/master)
  - Submit assignments via Pull Requests for code review
  - Use consistent naming conventions with course identifier

  ### 2. Professional Branching Strategy
  Each assignment should follow this pattern:
  ```bash
  # Start new assignment
  git checkout main
  git pull upstream main
  git push origin main
  git checkout -b week01-assignment-name

  # Work on assignment in this branch
  # Submit via Pull Request when complete

  3. Directory Structure for Submissions

  Implement this structure in the course repository:
  course-repo/
  ├── assignments/
  │   └── COURSE_ID_FirstName_LastName/
  │       ├── week01/
  │       ├── week02/
  │       └── ...
  └── [other course materials]

  4. Git Configuration Requirements

  Students must configure Git with course identifier:
  git config user.name "FirstName LastName - COURSE_ID"
  git config user.email "student.email@university.edu"

  Implementation Specifications

  Required Files to Create/Modify:

  1. assignments/README.md - Clear submission workflow
  instructions
  2. quick-reference/git-commands.md - Essential Git commands for
   students
  3. setup/getting-started.md - Include Git setup in environment
  configuration
  4. .github/pull_request_template.md - Structure PR submissions
  5. Repository README.md - Include Git workflow overview

  Pull Request Workflow Details:

  Student Process:
  1. Fork course repository
  2. Clone their fork locally
  3. Add upstream remote to original course repo
  4. Create feature branch for each assignment
  5. Complete work in their assignment directory
  6. Submit Pull Request with specific template

  Instructor Process:
  1. Review Pull Request with line-by-line code review
  2. Provide feedback through PR comments
  3. Request changes if needed
  4. Approve and record grade when satisfactory
  5. Student merges their own PR after approval

  Educational Benefits to Emphasize:

  - Industry-standard workflow: Students learn real development
  practices
  - Code review skills: Both giving and receiving feedback
  - Version control mastery: Branching, merging, conflict
  resolution
  - Professional portfolio: GitHub history shows collaboration
  skills
  - Documentation practices: README files, commit messages, PR
  descriptions

  Course-Specific Adaptations Needed:

  Please customize for my course:
  - Course identifier: [SPECIFY YOUR COURSE CODE]
  - Assignment types: [SPECIFY: coding projects, written work,
  etc.]
  - Submission requirements: [SPECIFY: required files,
  documentation, etc.]
  - Grading integration: [SPECIFY: Canvas, other LMS, gradebook]

  Additional Requirements:

  FERPA Compliance:

  - Student work in public repositories (educational benefit)
  - Grades and detailed feedback in private LMS (Canvas/etc)
  - No sensitive personal information in Git commits

  Academic Integrity:

  - Clear timestamp tracking through Git commits
  - Individual work in separate directories
  - Plagiarism detection through commit history

  Student Support:

  - Troubleshooting guide for common Git issues
  - Quick-reference cards for essential commands
  - Progressive disclosure: basic workflow first, advanced
  features later

  Files That Should Be Created:

  1. Git workflow documentation explaining the complete process
  2. Student submission templates with required directory
  structure
  3. Quick-reference guides for common Git operations
  4. Troubleshooting section for Git-related issues
  5. PR template to ensure consistent submission format

  Please implement this Git-based assignment submission system
  with clear documentation that helps students learn professional
   development practices while maintaining academic rigor and
  FERPA compliance.

  Success Criteria:

  When complete, students should be able to:
  - Fork and clone the course repository successfully
  - Create appropriate feature branches for assignments
  - Submit professional Pull Requests with proper documentation
  - Understand basic Git workflow used in software development
  - Build a GitHub portfolio that demonstrates collaboration
  skills

  The system should reduce instructor grading overhead while
  providing better feedback mechanisms and teaching valuable
  professional skills.

  This prompt provides all the essential elements needed to
  replicate the CSCI 347 Git workflow in any other course, with
  clear specifications and customization points for different
  course contexts.
