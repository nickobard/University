#!/usr/bin/env python3

from weasyprint import HTML

HTML('http://localhost:8000/about?pure_report=yes').write_pdf('bardanik.pdf')
