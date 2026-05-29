const express = require('express');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');

const app = express();
app.use(express.json());

// Main base point referencing where your project root directory lives
const COMPILER_ROOT = path.join(__dirname, '..', '..');



app.post('/api/compile', (req, res) => {
    const { files, mainFile } = req.body;
    
    
    // 1. Verify the payload data contains the code map and starting entry point
    if (!files || !mainFile || !files[mainFile]) {
        return res.status(400).json({ error: "Missing source code payload or entrypoint definitions." });
    }


    // 2. Isolate compilation side effects inside a dedicated workspace folder
    const workspace = path.join(COMPILER_ROOT, 'build_workspace');

    if (!fs.existsSync(workspace)) {
        fs.mkdirSync(workspace);
    }


    // 3. Write all individual tab data records straight onto the disk tracks
    Object.entries(files).forEach(([name, content]) => {
        fs.writeFileSync(path.join(workspace, name), content);
    });


    const binary = path.join(COMPILER_ROOT, 'compiler.exe');


    // 4. Run your underlying C compiler engine binary directly inside the workspace context
    exec(`"${binary}" "${mainFile}"`, { cwd: workspace }, (err, stdout, stderr) => {
        
        // Merge standard tracking out logs and channel diagnostics together
        const fullLogs = stdout + "\n" + (stderr || "");


        try {
            // 5. Establish exact path markers for all three visualization data structures
            const astPath     = path.join(workspace, 'ast.json');
            const cfgPath     = path.join(workspace, 'cfg.json');
            const symbolsPath = path.join(workspace, 'symbols.json');


            // 6. Inspect tracking maps and safely extract the generated JSON strings
            const astData    = fs.existsSync(astPath) ? JSON.parse(fs.readFileSync(astPath, 'utf8')) : null;
            const cfgData    = fs.existsSync(cfgPath) ? JSON.parse(fs.readFileSync(cfgPath, 'utf8')) : null;
            const symbolData = fs.existsSync(symbolsPath) ? JSON.parse(fs.readFileSync(symbolsPath, 'utf8')) : null;


            // 7. Parse intermediate Three-Address Code strings directly out from standard output
            const tac_instructions = [];
            let readingTAC = false;
            
            stdout.split('\n').forEach(line => {
                if (line.includes("=========== Three-Address Code")) { 
                    readingTAC = true; 
                    return; 
                }
                if (line.includes("=========== Control Flow Graph")) { 
                    readingTAC = false; 
                }
                if (readingTAC && line.trim()) {
                    tac_instructions.push(line.trim());
                }
            });


            // 8. Quantify quick structural metadata metrics for dashboard presentation
            const errors = (fullLogs.match(/\[Semantic Error\]/g) || []).length;
            const nodes  = astData ? JSON.stringify(astData).match(/"id"/g)?.length || 0 : 0;
            const blocks = cfgData?.nodes?.length || 0;


            // 9. Deliver the fully synchronized analysis data package back to the UI layout
            res.json({
                logs: fullLogs,
                ast: astData,
                cfg: cfgData,
                symbol_table: symbolData,
                tac_instructions: tac_instructions,
                metrics: { 
                    ast_nodes: nodes, 
                    cfg_blocks: blocks, 
                    errors: errors 
                }
            });


        } catch (fail) {
            console.error("Backend Parsing Error:", fail);
            res.status(500).json({ error: "Failed to read compiler output files.", logs: fullLogs });
        }
    });
});



const PORT = 5000;
app.listen(PORT, () => console.log(`🚀 Compiler Orchestration API active on port ${PORT}`));