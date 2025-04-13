# Mini-vote-system-using-c
A simple command-line voting system implemented in C, allowing voter registration, vote casting, representative appointment, and result tracking with a time-bound voting period.
Features

    Admin Functions:
        Appoint representatives.
        Set voting timeframe.
        View registered voters and results.
    Voter Functions:
        Register as a voter.
        Cast a vote for a representative.
        View current voting results.
    Data Persistence:
        Stores voters, representatives, votes, and timeframe in text files (voters.txt, reps.txt, votes.txt, timeframe.txt).
    Security:
        Admin access protected by a password (admin123).
        Ensures one vote per voter.
    Time-Bound Voting:
        Voting is only allowed within the admin-defined timeframe.

Prerequisites

    C Compiler: GCC, Clang, or any C99-compatible compiler.
    Code::Blocks (optional): For an IDE-based setup.
    Operating System: Windows, Linux, or macOS.
    Git: For cloning the repository.

Setup Instructions

    Clone the Repository:
    bash

git clone https://github.com/yourusername/ielts-prep-app.git
cd ielts-prep-app
Replace yourusername with the actual repository owner’s GitHub username.
Configure Compiler:

    Ensure your compiler supports C99.
    For Code::Blocks:
        Open the project or C file (main.c).
        Go to Settings > Compiler... > Compiler Flags.
        Add -std=c99 in Other compiler options.
    For GCC:
    bash

    gcc -std=c99 main.c -o voting_system

Compile the Program:

    In Code::Blocks: Click Build > Build (or Ctrl+F9).
    In Terminal:
    bash

    gcc -std=c99 main.c -o voting_system

Run the Program:

    In Code::Blocks: Click Build > Run (or F9).
    In Terminal:
    bash

./voting_system
On Windows, use:
bash

        voting_system.exe

Usage

    Main Menu:
        Admin Login: Enter password admin123 to access admin features.
        Voter Menu: Register or cast votes.
        Exit: Close the program.
    Admin Menu:
        Appoint representatives (max 10).
        Set voting timeframe (format: YYYY-MM-DD HH:MM:SS).
        View registered voters or voting results.
    Voter Menu:
        Register with a unique voter ID and name (max 100 voters).
        Cast a vote for a representative (only once per voter, within timeframe).
        View current results.
    Data Storage:
        Data is saved automatically to voters.txt, reps.txt, votes.txt, and timeframe.txt in the project directory.

File Structure

    main.c: Source code for the voting system.
    voters.txt: Stores voter data (ID, name, has_voted).
    reps.txt: Stores representative data (ID, name, vote_count).
    votes.txt: Tracks vote counts for representatives.
    timeframe.txt: Stores voting start and end times.

Contribution Guidelines

    Create a Branch:
    bash

git checkout -b yourname-feature
Replace yourname-feature with a descriptive name (e.g., add-login).
Make Changes:

    Edit main.c or add new files in your branch.
    Test thoroughly before committing.

Commit and Push:
bash
git add .
git commit -m "Describe your changes"
git push origin yourname-feature
Create a Pull Request:

    Go to the GitHub repository.
    Click Compare & pull request for your branch.
    Add a description and submit for review.

Sync with Main:

    To pull updates from the main branch:
    bash

        git checkout main
        git pull origin main
        git checkout yourname-feature
        git merge main
        Resolve conflicts if any.

Notes

    Database: This project uses text files for persistence, not a database like MySQL. If you meant to integrate with XAMPP’s MySQL (from your previous question), please clarify, and we can extend the project.
    Limitations:
        Maximum of 100 voters and 10 representatives.
        Admin password is hardcoded (admin123).
        Timeframe parsing assumes correct input format.
    Improvements:
        Add input validation for voter IDs and time formats.
        Encrypt the admin password.
        Support more voters/reps with dynamic memory allocation.

Troubleshooting

    Compiler Error: Ensure -std=c99 is set (see Setup Instructions).
    File Errors: Check that .txt files are writable in the project directory.
    Timeframe Issues: Verify the system clock matches the expected timezone.
    Other Issues: Contact the repository owner or raise an issue on GitHub.

License

This project is licensed under the MIT License. See LICENSE for details (if applicable).