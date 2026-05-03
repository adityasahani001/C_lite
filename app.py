import gradio as gr
import subprocess
import os
import sys

# Compiling C files
def compile_c_files():
    c_files = {
        "LA": "src/LA.c",
        "parser": "src/parser.c",
        "module4_TAC": "src/module4_TAC.c",
        "module5_optimizer": "src/module5_optimizer.c"
    }
    
    for exe_name, source_path in c_files.items():
        output_name = f"src/{exe_name}.exe" if os.name == 'nt' else f"src/{exe_name}"
        if not os.path.exists(output_name):
            print(f"Compiling {source_path}...")
            result = subprocess.run(['gcc', source_path, '-o', output_name], capture_output=True, text=True)
            if result.returncode != 0:
                print(f"Error compiling {source_path}:\n{result.stderr}")
            else:
                print(f"Successfully compiled {source_path}")

def run_executable(exe_name, input_text):
    exe_path = f"src/{exe_name}.exe" if os.name == 'nt' else f"./src/{exe_name}"
    try:
        result = subprocess.run(
            [exe_path],
            input=input_text,
            capture_output=True,
            text=True,
            timeout=5
        )
        return result.stdout + result.stderr
    except subprocess.TimeoutExpired:
        return "Execution timed out."
    except Exception as e:
        return f"Error executing {exe_name}: {str(e)}"

# Handlers for Gradio
def run_lexical_analyzer(code):
    if not code.strip().endswith("END"):
        code += "\nEND\n"
    return run_executable("LA", code)

def run_parser(expression):
    return run_executable("parser", expression)

def run_tac(expression):
    return run_executable("module4_TAC", expression)

def run_optimizer(tac_code):
    lines = tac_code.strip().split('\n')
    lines = [line for line in lines if line.strip()]
    num_lines = len(lines)
    input_text = f"{num_lines}\n" + "\n".join(lines) + "\n"
    return run_executable("module5_optimizer", input_text)

# Compile before starting Gradio
compile_c_files()

custom_css = """
/* Center main headers */
#main-header {
    text-align: center;
    font-family: 'Inter', sans-serif;
    margin-bottom: 2rem;
}
#main-header h1 {
    font-size: 3rem;
    font-weight: 900;
    margin-bottom: 0px;
}
#main-header .gradient-text {
    background: linear-gradient(90deg, #FF8A00, #E52E71);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
}
#main-header p {
    color: #A0AEC0;
    font-size: 1.2rem;
    margin-top: 5px;
}
/* Style the tabs to look like a pill menu */
.tabs {
    margin-top: 1rem !important;
    background: transparent !important;
}
.tab-nav {
    border-bottom: none !important;
    justify-content: center !important;
    gap: 1rem !important;
    margin-bottom: 1rem !important;
}
.tab-nav button {
    border: 1px solid #2D3748 !important;
    border-radius: 20px !important;
    padding: 8px 20px !important;
    background: #1A202C !important;
    color: #CBD5E0 !important;
    transition: all 0.3s ease !important;
}
.tab-nav button.selected {
    background: linear-gradient(90deg, #4FACFE, #00F2FE) !important;
    border: none !important;
    color: white !important;
    font-weight: bold !important;
    box-shadow: 0 4px 15px rgba(0, 242, 254, 0.4) !important;
}
/* Premium button styling */
button.primary {
    background: linear-gradient(90deg, #FF8A00, #E52E71) !important;
    border: none !important;
    color: white !important;
    font-weight: bold !important;
    border-radius: 8px !important;
    transition: transform 0.2s, box-shadow 0.2s !important;
}
button.primary:hover {
    transform: translateY(-2px);
    box-shadow: 0 8px 15px rgba(229, 46, 113, 0.4) !important;
}
/* Text area styling */
textarea {
    border-radius: 10px !important;
    border: 1px solid #2D3748 !important;
    transition: border-color 0.3s !important;
}
textarea:focus {
    border-color: #00F2FE !important;
    box-shadow: 0 0 0 2px rgba(0, 242, 254, 0.2) !important;
}
"""

with gr.Blocks(title="C-LITE Compiler", css=custom_css, theme=gr.themes.Base()) as app:
    gr.HTML("""
    <div id="main-header">
        <h1><span class="gradient-text">A MINI COMPILER : C-LITE</span> 🤖</h1>
        <p>Interact with the different phases of the C-LITE compiler.</p>
    </div>
    """)
    
    with gr.Tabs():
        with gr.Tab("ℹ️ About"):
            gr.Markdown("""
            ### Welcome to the C-LITE Compiler!
            This project is a mini compiler showcasing the core phases of compiling a C-like programming language. It is broken down into four independent modules that you can interact with:
            
            1. **📝 Lexical Analyzer**: Scans raw source code and converts sequences of characters into meaningful tokens (keywords, identifiers, operators, numbers).
            2. **🌳 Parser**: Evaluates mathematical expressions (supporting `+`, `-`, `*`, `/`) by checking them against grammar rules using recursive descent parsing.
            3. **⚙️ Three Address Code (TAC)**: An intermediate code generator that breaks down complex expressions into simple instructions, each having at most three operands.
            4. **✨ Optimizer**: Identifies identical and duplicate expressions in your TAC block and optimizes them to remove redundant calculations and variable assignments.
            
            Click on the tabs above to test each phase individually!
            """)

        with gr.Tab("📝 Lexical Analyzer"):
            gr.Markdown("Enter your C-LITE code below. The system automatically appends 'END' to signify the end of input.")
            with gr.Row():
                with gr.Column():
                    la_input = gr.Textbox(lines=10, placeholder="int main() {\n  int a = 5;\n}", label="Source Code")
                    la_button = gr.Button("Analyze", variant="primary")
                with gr.Column():
                    la_output = gr.Textbox(lines=15, label="Tokens")
            la_button.click(run_lexical_analyzer, inputs=la_input, outputs=la_output)
            
        with gr.Tab("🌳 Parser"):
            gr.Markdown("Enter an arithmetic expression to parse and evaluate (e.g., `5+3*2`).")
            with gr.Row():
                with gr.Column():
                    parser_input = gr.Textbox(lines=2, placeholder="5+3*2", label="Expression")
                    parser_button = gr.Button("Parse", variant="primary")
                with gr.Column():
                    parser_output = gr.Textbox(lines=5, label="Evaluation Result")
            parser_button.click(run_parser, inputs=parser_input, outputs=parser_output)
            
        with gr.Tab("⚙️ Three Address Code (TAC)"):
            gr.Markdown("Enter an arithmetic expression to generate its Three Address Code.")
            with gr.Row():
                with gr.Column():
                    tac_input = gr.Textbox(lines=2, placeholder="a+b*c", label="Expression")
                    tac_button = gr.Button("Generate TAC", variant="primary")
                with gr.Column():
                    tac_output = gr.Textbox(lines=10, label="TAC Output")
            tac_button.click(run_tac, inputs=tac_input, outputs=tac_output)
            
        with gr.Tab("✨ Optimizer"):
            gr.Markdown("Enter Three Address Code (TAC) lines to optimize. The number of lines is calculated automatically.")
            with gr.Row():
                with gr.Column():
                    opt_input = gr.Textbox(lines=10, placeholder="t1 = b * c\nt2 = a + t1\nt3 = b * c\nt4 = a + t3", label="TAC Lines")
                    opt_button = gr.Button("Optimize", variant="primary")
                with gr.Column():
                    opt_output = gr.Textbox(lines=10, label="Optimized TAC Output")
            opt_button.click(run_optimizer, inputs=opt_input, outputs=opt_output)

if __name__ == "__main__":
    app.launch(theme=gr.themes.Soft())
