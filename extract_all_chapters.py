#!/usr/bin/env python3
"""
Batch Chapter Extractor for C++ Crash Course
Extracts all chapters based on predefined page ranges.
You'll need to update the CHAPTER_RANGES dictionary with actual page numbers.
"""

import PyPDF2
from pathlib import Path
import sys

# UPDATE THESE PAGE RANGES BASED ON YOUR TEXTBOOK'S TABLE OF CONTENTS
CHAPTER_RANGES = {
    "01_introduction": (1, 25),          # Update with actual pages
    "02_types_and_references": (26, 60),
    "03_operators_and_expressions": (61, 90),
    "04_control_flow": (91, 120),
    "05_functions": (121, 150),
    "06_objects_and_classes": (151, 200),
    "07_inheritance": (201, 240),
    "08_templates": (241, 280),
    "09_containers": (281, 320),
    "10_algorithms": (321, 360),
    "11_utilities": (361, 400),
    "12_concurrency": (401, 440),
    "13_filesystems": (441, 480),
    "14_network_programming": (481, 520),
    "15_application_programming": (521, 560),
}

def get_pdf_info(pdf_path):
    """Get basic information about the PDF."""
    try:
        with open(pdf_path, 'rb') as pdf_file:
            pdf_reader = PyPDF2.PdfReader(pdf_file)
            total_pages = len(pdf_reader.pages)
            print(f"PDF Information:")
            print(f"  Total pages: {total_pages}")
            print(f"  File: {pdf_path}")
            return total_pages
    except Exception as e:
        print(f"Error reading PDF: {e}")
        return None

def extract_chapter(pdf_reader, start_page, end_page, output_file):
    """Extract a single chapter from the PDF."""
    pdf_writer = PyPDF2.PdfWriter()
    
    # Convert to 0-based indexing
    start_idx = start_page - 1
    end_idx = end_page
    
    # Extract pages
    for page_num in range(start_idx, end_idx):
        if page_num < len(pdf_reader.pages):
            pdf_writer.add_page(pdf_reader.pages[page_num])
    
    # Save chapter
    with open(output_file, 'wb') as output_pdf:
        pdf_writer.write(output_pdf)
    
    return end_page - start_page + 1

def extract_all_chapters(pdf_path, output_dir="chapters"):
    """Extract all chapters from the PDF."""
    output_path = Path(output_dir)
    output_path.mkdir(exist_ok=True)
    
    try:
        with open(pdf_path, 'rb') as pdf_file:
            pdf_reader = PyPDF2.PdfReader(pdf_file)
            total_pages = len(pdf_reader.pages)
            
            print(f"Extracting chapters from {pdf_path}")
            print(f"Total pages in PDF: {total_pages}")
            print(f"Output directory: {output_path.absolute()}")
            print("-" * 50)
            
            for chapter_name, (start_page, end_page) in CHAPTER_RANGES.items():
                if end_page > total_pages:
                    print(f"Warning: Chapter {chapter_name} ends at page {end_page}, but PDF only has {total_pages} pages")
                    continue
                
                output_file = output_path / f"{chapter_name}.pdf"
                pages_extracted = extract_chapter(pdf_reader, start_page, end_page, output_file)
                
                print(f"✓ {chapter_name}: pages {start_page}-{end_page} ({pages_extracted} pages) -> {output_file}")
            
            print("-" * 50)
            print("Extraction complete!")
            
    except FileNotFoundError:
        print(f"Error: PDF file '{pdf_path}' not found.")
        return False
    except Exception as e:
        print(f"Error extracting chapters: {e}")
        return False
    
    return True

def main():
    if len(sys.argv) < 2:
        print("Usage: python extract_all_chapters.py <pdf_path> [output_directory]")
        print("\nExample: python extract_all_chapters.py 'C++ Crash Course A Fast-Paced Introduction by Josh Lospinoso.pdf'")
        print("\nNote: You need to update the CHAPTER_RANGES dictionary with actual page numbers from your PDF.")
        sys.exit(1)
    
    pdf_path = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else "chapters"
    
    # First, show PDF info to help determine page ranges
    total_pages = get_pdf_info(pdf_path)
    if total_pages is None:
        sys.exit(1)
    
    print("\n" + "="*60)
    print("IMPORTANT: Update CHAPTER_RANGES in this script!")
    print("="*60)
    print("The current page ranges are placeholders.")
    print("You need to:")
    print("1. Look at the table of contents in your PDF")
    print("2. Update the CHAPTER_RANGES dictionary with actual page numbers")
    print("3. Run this script again")
    print("="*60)
    
    response = input("\nHave you updated the page ranges? (y/n): ")
    if response.lower() != 'y':
        print("Please update CHAPTER_RANGES first, then run again.")
        sys.exit(0)
    
    success = extract_all_chapters(pdf_path, output_dir)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()