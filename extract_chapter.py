#!/usr/bin/env python3
"""
PDF Chapter Extractor for C++ Crash Course
Extracts individual chapters from the textbook PDF for course development.
"""

import PyPDF2
import argparse
import sys
from pathlib import Path

def extract_chapter(pdf_path, start_page, end_page, output_path, chapter_name):
    """
    Extract pages from PDF and save as a new PDF file.
    
    Args:
        pdf_path (str): Path to the source PDF
        start_page (int): Starting page number (1-based)
        end_page (int): Ending page number (1-based, inclusive)
        output_path (str): Directory to save extracted chapter
        chapter_name (str): Name for the output file
    """
    try:
        with open(pdf_path, 'rb') as pdf_file:
            pdf_reader = PyPDF2.PdfReader(pdf_file)
            pdf_writer = PyPDF2.PdfWriter()
            
            # Convert to 0-based indexing
            start_idx = start_page - 1
            end_idx = end_page
            
            # Validate page range
            total_pages = len(pdf_reader.pages)
            if start_idx < 0 or end_idx > total_pages:
                print(f"Error: Page range {start_page}-{end_page} invalid. PDF has {total_pages} pages.")
                return False
            
            # Extract pages
            for page_num in range(start_idx, end_idx):
                pdf_writer.add_page(pdf_reader.pages[page_num])
            
            # Create output directory if it doesn't exist
            output_dir = Path(output_path)
            output_dir.mkdir(exist_ok=True)
            
            # Save extracted chapter
            output_file = output_dir / f"{chapter_name}.pdf"
            with open(output_file, 'wb') as output_pdf:
                pdf_writer.write(output_pdf)
            
            print(f"Successfully extracted pages {start_page}-{end_page} to {output_file}")
            print(f"Extracted {end_page - start_page + 1} pages")
            return True
            
    except FileNotFoundError:
        print(f"Error: PDF file '{pdf_path}' not found.")
        return False
    except Exception as e:
        print(f"Error extracting chapter: {e}")
        return False

def main():
    parser = argparse.ArgumentParser(description="Extract chapters from C++ Crash Course PDF")
    parser.add_argument("pdf_path", help="Path to the C++ Crash Course PDF")
    parser.add_argument("start_page", type=int, help="Starting page number (1-based)")
    parser.add_argument("end_page", type=int, help="Ending page number (1-based, inclusive)")
    parser.add_argument("-o", "--output", default="chapters", help="Output directory (default: chapters)")
    parser.add_argument("-n", "--name", help="Chapter name (default: chapter_X)")
    
    args = parser.parse_args()
    
    # Generate default chapter name if not provided
    if not args.name:
        args.name = f"chapter_{args.start_page}_{args.end_page}"
    
    success = extract_chapter(
        args.pdf_path,
        args.start_page,
        args.end_page,
        args.output,
        args.name
    )
    
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()