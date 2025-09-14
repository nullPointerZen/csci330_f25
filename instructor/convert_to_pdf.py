#!/usr/bin/env python3
"""
Convert Markdown to PDF using HTML as intermediate format
Requires: pip install markdown weasyprint
"""

import sys
import os

def check_dependencies():
    """Check if required packages are installed"""
    packages_needed = []

    try:
        import markdown
    except ImportError:
        packages_needed.append('markdown')

    try:
        import weasyprint
    except ImportError:
        packages_needed.append('weasyprint')

    if packages_needed:
        print(f"Installing required packages: {', '.join(packages_needed)}")
        import subprocess
        subprocess.check_call([sys.executable, '-m', 'pip', 'install'] + packages_needed)
        print("Packages installed successfully. Please run the script again.")
        sys.exit(0)

def convert_md_to_pdf(md_file, pdf_file):
    """Convert markdown file to PDF"""
    import markdown
    from weasyprint import HTML, CSS

    # Read markdown content
    with open(md_file, 'r', encoding='utf-8') as f:
        md_content = f.read()

    # Convert markdown to HTML with extensions
    md = markdown.Markdown(extensions=['extra', 'codehilite', 'tables', 'toc'])
    html_content = md.convert(md_content)

    # Create full HTML document with styling
    html_template = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="utf-8">
        <title>GitHub Instructor Cheatsheet</title>
        <style>
            @page {{
                size: A4;
                margin: 1.5cm;
            }}
            body {{
                font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Helvetica, Arial, sans-serif;
                font-size: 11pt;
                line-height: 1.6;
                color: #333;
                max-width: 100%;
            }}
            h1 {{
                color: #0366d6;
                border-bottom: 3px solid #e1e4e8;
                padding-bottom: 0.3em;
                margin-top: 1.5em;
                margin-bottom: 0.8em;
                font-size: 1.8em;
                page-break-after: avoid;
            }}
            h2 {{
                color: #0366d6;
                border-bottom: 1px solid #e1e4e8;
                padding-bottom: 0.2em;
                margin-top: 1.2em;
                margin-bottom: 0.6em;
                font-size: 1.4em;
                page-break-after: avoid;
            }}
            h3 {{
                color: #333;
                margin-top: 1em;
                margin-bottom: 0.5em;
                font-size: 1.2em;
                page-break-after: avoid;
            }}
            code {{
                background-color: #f6f8fa;
                padding: 0.2em 0.4em;
                border-radius: 3px;
                font-family: 'SF Mono', Monaco, Consolas, 'Liberation Mono', 'Courier New', monospace;
                font-size: 0.9em;
            }}
            pre {{
                background-color: #f6f8fa;
                padding: 1em;
                border-radius: 6px;
                overflow-x: auto;
                line-height: 1.4;
                page-break-inside: avoid;
            }}
            pre code {{
                background-color: transparent;
                padding: 0;
                font-size: 0.85em;
            }}
            blockquote {{
                border-left: 4px solid #0366d6;
                padding-left: 1em;
                margin-left: 0;
                color: #666;
            }}
            table {{
                border-collapse: collapse;
                width: 100%;
                margin: 1em 0;
                page-break-inside: avoid;
            }}
            table th {{
                background-color: #f6f8fa;
                border: 1px solid #d1d5da;
                padding: 0.5em 1em;
                font-weight: 600;
                text-align: left;
            }}
            table td {{
                border: 1px solid #d1d5da;
                padding: 0.5em 1em;
            }}
            table tr:nth-child(even) {{
                background-color: #f9f9f9;
            }}
            ul, ol {{
                margin: 0.5em 0;
                padding-left: 2em;
            }}
            li {{
                margin: 0.3em 0;
            }}
            strong {{
                color: #000;
                font-weight: 600;
            }}
            em {{
                font-style: italic;
            }}
            hr {{
                border: none;
                border-top: 2px solid #e1e4e8;
                margin: 2em 0;
            }}
            a {{
                color: #0366d6;
                text-decoration: none;
            }}
            a:hover {{
                text-decoration: underline;
            }}
            .emoji {{
                width: 1em;
                height: 1em;
                vertical-align: middle;
            }}
            /* Prevent awkward breaks */
            h1, h2, h3, h4, h5, h6 {{
                page-break-after: avoid;
            }}
            p {{
                orphans: 3;
                widows: 3;
            }}
            /* Code block specific styling */
            .codehilite {{
                background-color: #f6f8fa;
                padding: 1em;
                border-radius: 6px;
                margin: 1em 0;
            }}
        </style>
    </head>
    <body>
        {html_content}
    </body>
    </html>
    """

    # Convert HTML to PDF
    print(f"Converting {md_file} to {pdf_file}...")
    HTML(string=html_template).write_pdf(pdf_file)
    print(f"Successfully created: {pdf_file}")

if __name__ == "__main__":
    check_dependencies()

    md_file = "GITHUB_INSTRUCTOR_CHEATSHEET.md"
    pdf_file = "GITHUB_INSTRUCTOR_CHEATSHEET.pdf"

    if not os.path.exists(md_file):
        print(f"Error: {md_file} not found in current directory")
        sys.exit(1)

    try:
        convert_md_to_pdf(md_file, pdf_file)
    except Exception as e:
        print(f"Error during conversion: {e}")
        sys.exit(1)