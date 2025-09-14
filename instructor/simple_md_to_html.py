#!/usr/bin/env python3
"""
Simple Markdown to HTML converter for printing to PDF
Uses only markdown library (no external system dependencies)
"""

import sys
import os

# Check for markdown library
try:
    import markdown
except ImportError:
    print("Installing markdown library...")
    import subprocess
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'markdown'])
    import markdown

def convert_md_to_html(md_file, html_file):
    """Convert markdown file to HTML with print-friendly styling"""

    # Read markdown content
    with open(md_file, 'r', encoding='utf-8') as f:
        md_content = f.read()

    # Convert markdown to HTML with extensions
    md = markdown.Markdown(extensions=['extra', 'tables', 'toc', 'fenced_code'])
    html_content = md.convert(md_content)

    # Create full HTML document with print-optimized styling
    html_template = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>GitHub Instructor Cheatsheet</title>
    <style>
        /* Reset and base styles */
        * {{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }}

        body {{
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', 'Helvetica Neue', Arial, sans-serif;
            font-size: 14px;
            line-height: 1.6;
            color: #24292e;
            background: white;
            padding: 20px;
            max-width: 900px;
            margin: 0 auto;
        }}

        /* Typography */
        h1 {{
            color: #0366d6;
            font-size: 28px;
            margin: 30px 0 20px 0;
            padding-bottom: 10px;
            border-bottom: 3px solid #e1e4e8;
            page-break-after: avoid;
        }}

        h2 {{
            color: #0366d6;
            font-size: 22px;
            margin: 25px 0 15px 0;
            padding-bottom: 8px;
            border-bottom: 1px solid #e1e4e8;
            page-break-after: avoid;
        }}

        h3 {{
            color: #24292e;
            font-size: 18px;
            margin: 20px 0 10px 0;
            font-weight: 600;
            page-break-after: avoid;
        }}

        h4 {{
            color: #24292e;
            font-size: 16px;
            margin: 15px 0 10px 0;
            font-weight: 600;
        }}

        p {{
            margin: 10px 0;
            orphans: 3;
            widows: 3;
        }}

        /* Lists */
        ul, ol {{
            margin: 10px 0;
            padding-left: 30px;
        }}

        li {{
            margin: 5px 0;
        }}

        /* Code blocks */
        code {{
            font-family: 'SF Mono', Monaco, Consolas, 'Liberation Mono', 'Courier New', monospace;
            font-size: 13px;
            background-color: #f6f8fa;
            padding: 2px 6px;
            border-radius: 3px;
        }}

        pre {{
            background-color: #f6f8fa;
            border: 1px solid #e1e4e8;
            border-radius: 6px;
            padding: 16px;
            overflow-x: auto;
            margin: 15px 0;
            page-break-inside: avoid;
        }}

        pre code {{
            background-color: transparent;
            padding: 0;
            border-radius: 0;
            font-size: 12px;
            line-height: 1.45;
        }}

        /* Tables */
        table {{
            border-collapse: collapse;
            width: 100%;
            margin: 15px 0;
            page-break-inside: avoid;
        }}

        table th {{
            background-color: #f6f8fa;
            border: 1px solid #d1d5da;
            padding: 8px 12px;
            font-weight: 600;
            text-align: left;
        }}

        table td {{
            border: 1px solid #d1d5da;
            padding: 8px 12px;
        }}

        table tr:nth-child(even) {{
            background-color: #fafbfc;
        }}

        /* Blockquotes */
        blockquote {{
            border-left: 4px solid #0366d6;
            padding-left: 16px;
            margin: 15px 0;
            color: #6a737d;
        }}

        /* Links */
        a {{
            color: #0366d6;
            text-decoration: none;
        }}

        a:hover {{
            text-decoration: underline;
        }}

        /* Horizontal rules */
        hr {{
            border: none;
            border-top: 2px solid #e1e4e8;
            margin: 30px 0;
        }}

        /* Strong and emphasis */
        strong {{
            font-weight: 600;
            color: #000;
        }}

        em {{
            font-style: italic;
        }}

        /* Print styles */
        @media print {{
            body {{
                font-size: 11pt;
                padding: 0;
                max-width: 100%;
            }}

            h1 {{
                font-size: 20pt;
                page-break-after: avoid;
            }}

            h2 {{
                font-size: 16pt;
                page-break-after: avoid;
            }}

            h3 {{
                font-size: 14pt;
                page-break-after: avoid;
            }}

            pre {{
                font-size: 9pt;
                page-break-inside: avoid;
            }}

            code {{
                font-size: 9pt;
            }}

            table {{
                font-size: 10pt;
                page-break-inside: avoid;
            }}

            /* Avoid breaking inside important elements */
            ul, ol {{
                page-break-inside: avoid;
            }}

            /* Add page breaks at major sections */
            h1 {{
                page-break-before: auto;
            }}

            /* Hide non-essential elements */
            a {{
                color: #0366d6 !important;
                text-decoration: none !important;
            }}
        }}

        /* Special formatting for emoji-like indicators */
        h2:before {{
            margin-right: 8px;
        }}
    </style>
</head>
<body>
    <div class="container">
        {html_content}
    </div>

    <script>
        // Add print instructions at the top when loaded
        if (window.location.protocol === 'file:') {{
            const instructions = document.createElement('div');
            instructions.style.cssText = 'background: #f0f7ff; border: 2px solid #0366d6; padding: 15px; margin-bottom: 30px; border-radius: 6px;';
            instructions.innerHTML = '<strong>To convert to PDF:</strong> Press Cmd+P (Mac) or Ctrl+P (Windows/Linux), then choose "Save as PDF" from the printer options.';
            document.body.insertBefore(instructions, document.body.firstChild);
        }}
    </script>
</body>
</html>"""

    # Write HTML file
    with open(html_file, 'w', encoding='utf-8') as f:
        f.write(html_template)

    print(f"✅ Successfully created: {html_file}")
    return html_file

if __name__ == "__main__":
    md_file = "GITHUB_INSTRUCTOR_CHEATSHEET.md"
    html_file = "GITHUB_INSTRUCTOR_CHEATSHEET.html"

    if not os.path.exists(md_file):
        print(f"Error: {md_file} not found in current directory")
        sys.exit(1)

    try:
        output_file = convert_md_to_html(md_file, html_file)
        print(f"\n📄 HTML file created: {output_file}")
        print("\n🖨️  TO CREATE PDF:")
        print("   1. Open the HTML file in your browser")
        print("   2. Press Cmd+P (Mac) or Ctrl+P (Windows/Linux)")
        print("   3. Choose 'Save as PDF' from the printer dropdown")
        print("   4. Adjust settings if needed (margins, scale, etc.)")
        print("   5. Click 'Save'\n")

        # Try to open in default browser
        import webbrowser
        full_path = os.path.abspath(html_file)
        print(f"🌐 Opening in browser: file://{full_path}")
        webbrowser.open(f"file://{full_path}")

    except Exception as e:
        print(f"Error during conversion: {e}")
        sys.exit(1)