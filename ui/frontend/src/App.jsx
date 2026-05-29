import React, { useState, useEffect } from 'react';
import Editor from '@monaco-editor/react';
import ReactFlow, { MiniMap, Controls, Background, useNodesState, useEdgesState } from 'reactflow';
import { Folder, FileCode, Play, Layers, FilePlus, Trash2 } from 'lucide-react';
import 'reactflow/dist/style.css';

const INITIAL_WORKSPACE = {
  "main.c": `int main() {\n    int i = 0;\n    int sum = 0;\n    while (i < 10) {\n        sum = sum + i;\n        i = i + 1;\n    }\n    return 0;\n}`
};



export default function App() {

  const [files, setFiles] = useState(INITIAL_WORKSPACE);
  const [activeFile, setActiveFile] = useState("main.c");
  const [newFileName, setNewFileName] = useState("");
  const [activeTab, setActiveTab] = useState("logs"); 
  const [compilation, setCompilation] = useState(null);
  const [isCompiling, setIsCompiling] = useState(false);

  const [nodes, setNodes, onNodesChange] = useNodesState([]);
  const [edges, setEdges, onEdgesChange] = useEdgesState([]);



  // Dynamically appends a new editable code module file to the workspace state layout
  const addWorkspaceFile = () => {

    if (!newFileName.trim() || files[newFileName]) {
        return;
    }

    const cleanName = newFileName.endsWith('.c') ? newFileName : `${newFileName}.c`;
    
    setFiles({ ...files, [cleanName]: `// Module file: ${cleanName}\n` });
    setActiveFile(cleanName);
    setNewFileName("");
  };



  // Deletes a specific module asset from the file explorer sidebar tree
  const dropWorkspaceFile = (filename, e) => {

    e.stopPropagation();
    
    const copy = { ...files };
    delete copy[filename];
    
    setFiles(copy);
    
    if (activeFile === filename) {
        setActiveFile(Object.keys(copy)[0] || "");
    }
  };



  // Transmits the entire workspace map to the Node server to coordinate execution passes
  const runCompilerPipeline = async () => {

    setIsCompiling(true);
    setActiveTab("logs");

    try {
      const res = await fetch('/api/compile', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ files, mainFile: activeFile })
      });
      
      const data = await res.json();
      setCompilation(data);

    } catch (err) {
      console.error("API link broken:", err);
    } finally {
      setIsCompiling(false);
    }
  };



  // Synchronizes the application tab selections directly with updated parsing representations
  useEffect(() => {

    if (!compilation) {
        return;
    }


    // ----------------=========================================----------------
    // 1. ABSTRACT SYNTAX TREE RENDERING PIPELINE
    // ----------------=========================================----------------
    if (activeTab === 'ast' && compilation.ast) {
      const n = []; 
      const e = [];

      function parseTree(node, x = 250, y = 50, pId = null) {
        if (!node) return;
        const id = `ast-${node.id}`;
        
        n.push({
          id, 
          position: { x, y },
          data: { label: node.value || `Node [Type ${node.type}]` },
          style: { background: '#2d2d2d', color: '#4ec9b0', border: '1px solid #569cd6', borderRadius: '4px', fontSize: '11px', padding: '5px' }
        });
        
        if (pId) {
            e.push({ id: `e-${pId}-${id}`, source: pId, target: id, animated: true });
        }
        
        // Spread branches wide apart to prevent overlapping nodes on screen
        parseTree(node.left, x - 150, y + 80, id);
        parseTree(node.right, x + 150, y + 80, id);
        parseTree(node.third, x, y + 100, id);
        parseTree(node.next, x, y + 130, id); 
      }

      parseTree(compilation.ast);
      setNodes(n); 
      setEdges(e);
    }


    // ----------------=========================================----------------
    // 2. CONTROL FLOW GRAPH RENDERING PIPELINE
    // ----------------=========================================----------------
    if (activeTab === 'cfg' && compilation.cfg) {

      const n = compilation.cfg.nodes.map((block, idx) => ({
        id: `cfg-${block.id}`, 
        position: { x: 200, y: idx * 140 + 40 },
        data: { label: block.label },
        style: { background: '#1e1e1e', color: '#fff', border: '1px solid #0e639c', padding: '8px', fontFamily: 'monospace', fontSize: '11px', width: 220 }
      }));

      const e = compilation.cfg.edges.map(edge => ({
        id: `e-cfg-${edge.from}-${edge.to}`, 
        source: `cfg-${edge.from}`, 
        target: `cfg-${edge.to}`,
        label: edge.type, 
        arrows: 'to',
        style: { stroke: edge.type === 'true/fallthrough' ? '#4ec9b0' : '#f44336' }, 
        animated: true
      }));

      setNodes(n); 
      setEdges(e);
    }

  }, [activeTab, compilation]);



  return (
    <div className="flex flex-col h-screen w-screen bg-[#1e1e1e] text-[#d4d4d4] overflow-hidden">
      
      {/* Top Application Header Bar */}
      <header className="flex items-center justify-between px-4 py-2 bg-[#2d2d2d] border-b border-[#3c3c3c]">
        <div className="flex items-center gap-2">
          <Layers className="text-[#569cd6] w-5 h-5" />
          <h1 className="text-xs font-semibold text-white tracking-wider uppercase">Mini-C Visual Studio IDE</h1>
        </div>
        
        <button onClick={runCompilerPipeline} disabled={isCompiling} className="flex items-center gap-2 bg-[#0e639c] hover:bg-[#1177bb] disabled:bg-[#3c3c3c] text-white text-xs font-bold px-4 py-1.5 rounded shadow">
          <Play className={`w-3.5 h-3.5 ${isCompiling ? 'animate-spin' : ''}`} />
          {isCompiling ? 'Compiling Code...' : 'Compile Project'}
        </button>
      </header>


      <div className="flex flex-1 w-full min-h-0">
        
        {/* Project Explorer Directory Structure */}
        <aside className="w-56 bg-[#252526] border-r border-[#3c3c3c] flex flex-col p-3">
          <span className="text-[10px] font-bold uppercase text-gray-500 tracking-wider flex items-center gap-1.5 mb-2">
            <Folder className="w-3.5 h-3.5" /> Project Directory
          </span>
          
          <div className="flex items-center gap-1 mb-3 bg-[#1e1e1e] border border-[#3c3c3c] p-1 rounded">
            <input type="text" placeholder="filename.c" value={newFileName} onChange={e => setNewFileName(e.target.value)} className="bg-transparent text-xs text-[#9cdcfe] w-full px-1 outline-none font-mono" />
            <button onClick={addWorkspaceFile} className="p-0.5 text-gray-400 hover:text-white">
              <FilePlus className="w-4 h-4" />
            </button>
          </div>
          
          <div className="flex-1 space-y-0.5 overflow-y-auto">
            {Object.keys(files).map(name => (
              <div key={name} onClick={() => setActiveFile(name)} className={`flex items-center justify-between px-2 py-1 rounded text-xs font-mono cursor-pointer ${activeFile === name ? 'bg-[#37373d] text-white border-l-2 border-[#0e639c]' : 'hover:bg-[#2a2a2b] text-gray-400'}`}>
                <div className="flex items-center gap-1.5 truncate">
                  <FileCode className="w-3.5 h-3.5 text-[#569cd6]" />
                  <span>{name}</span>
                </div>
                {name !== 'main.c' && <Trash2 onClick={e => dropWorkspaceFile(name, e)} className="w-3.5 h-3.5 text-gray-500 hover:text-red-400" />}
              </div>
            ))}
          </div>
        </aside>


        {/* Central Source Code Tabbed Editor Panel */}
        <main className="flex-1 flex flex-col min-w-0 bg-[#1e1e1e]">
          <div className="flex bg-[#2d2d2d] border-b border-[#3c3c3c]">
            {Object.keys(files).map(name => (
              <button key={name} onClick={() => setActiveFile(name)} className={`px-4 py-1.5 border-r border-[#252526] text-xs font-mono ${activeFile === name ? 'bg-[#1e1e1e] text-white border-t border-[#0e639c]' : 'text-gray-400'}`}>
                {name}
              </button>
            ))}
          </div>
          
          <div className="flex-1 w-full h-full relative">
            <Editor height="100%" theme="vs-dark" path={activeFile} defaultLanguage="c" value={files[activeFile]} onChange={val => setFiles({...files, [activeFile]: val})} options={{ fontSize: 13, fontFamily: 'Consolas, monospace', minimap: { enabled: false } }} />
          </div>
        </main>


        {/* Compilation Analysis Tabs Panel */}
        <section className="w-[45%] bg-[#252526] border-l border-[#3c3c3c] flex flex-col min-w-0">
          <div className="flex bg-[#2d2d2d] border-b border-[#3c3c3c] text-[11px] font-medium">
            {['logs', 'ast', 'symbols', 'tac', 'cfg', 'stats'].map(tab => (
              <button key={tab} onClick={() => setActiveTab(tab)} className={`flex-1 py-2 text-center uppercase tracking-wider ${activeTab === tab ? "text-white bg-[#252526] font-bold border-b-2 border-[#0e639c]" : "text-gray-400 hover:text-white"}`}>
                {tab}
              </button>
            ))}
          </div>
          
          <div className="flex-1 min-h-0 p-3 overflow-auto">
            
            {/* Terminal Streams Output Tab */}
            {activeTab === "logs" && (
              <pre className="h-full bg-[#1e1e1e] p-3 rounded border border-[#3c3c3c] font-mono text-xs text-[#ce9178] overflow-auto whitespace-pre-wrap">
                {compilation ? compilation.logs : "Write source files and click Compile Project."}
              </pre>
            )}


            {/* Graph Render Visualization Window (React Flow Context) */}
            {(activeTab === "ast" || activeTab === "cfg") && (
              <div className="w-full h-full bg-[#1e1e1e] rounded border border-[#3c3c3c]">
                <ReactFlow nodes={nodes} edges={edges} onNodesChange={onNodesChange} onEdgesChange={onEdgesChange} fitView>
                  <Background color="#333" gap={12} />
                  <Controls />
                  <MiniMap nodeColor={() => '#2d2d2d'} />
                </ReactFlow>
              </div>
            )}


            {/* Active Registered Identifiers Scope Snapshot Tab */}
            {activeTab === "symbols" && (
              <div className="space-y-3 font-mono text-xs">
                {compilation && compilation.symbol_table ? Object.entries(compilation.symbol_table).map(([scope, vars]) => (
                  <div key={scope} className="border border-[#3c3c3c] rounded bg-[#1e1e1e] overflow-hidden">
                    <div className="bg-[#2d2d2d] px-2 py-1 text-[#4ec9b0] font-bold">{scope}</div>
                    <table className="w-full text-left">
                      <thead>
                        <tr className="bg-[#252526] text-gray-400 border-b border-[#3c3c3c]">
                          <th className="p-1">Name</th>
                          <th className="p-1">Type</th>
                          <th className="p-1">Kind</th>
                        </tr>
                      </thead>
                      <tbody>
                        {vars.map((v, i) => (
                          <tr key={i} className="border-b border-[#2d2d2d] hover:bg-[#252526]">
                            <td className="p-1 text-[#9cdcfe] font-bold">{v.name}</td>
                            <td className="p-1 text-[#569cd6]">{v.type}</td>
                            <td className="p-1 text-gray-400">{v.category}</td>
                          </tr>
                        ))}
                      </tbody>
                    </table>
                  </div>
                )) : <div className="text-center text-gray-500">No active symbol layouts mapped.</div>}
              </div>
            )}


            {/* Linear Three-Address Code Quadruples Sequence Tab */}
            {activeTab === "tac" && (
              <div className="bg-[#1e1e1e] border border-[#3c3c3c] rounded overflow-hidden font-mono text-xs">
                <table className="w-full text-left">
                  <thead className="bg-[#2d2d2d] text-gray-400 border-b border-[#3c3c3c]">
                    <tr>
                      <th className="p-1.5 w-12 text-center border-r border-[#3c3c3c]">Line</th>
                      <th className="p-1.5 pl-3 text-[#4ec9b0]">Quadruple Statement</th>
                    </tr>
                  </thead>
                  <tbody>
                    {compilation ? compilation.tac_instructions.map((instr, idx) => (
                      <tr key={idx} className="border-b border-[#2d2d2d] hover:bg-[#252526]">
                        <td className="p-1 text-center text-gray-500 border-r border-[#3c3c3c] bg-[#1a1a1a]">{idx + 1}</td>
                        <td className="p-1 pl-4 text-[#dcdcaa]">{instr}</td>
                      </tr>
                    )) : <tr><td colSpan="2" className="p-3 text-center text-gray-500">Intermediate representation is clear.</td></tr>}
                  </tbody>
                </table>
              </div>
            )}


            {/* Pipeline Resource Metric Indicators Dashboard Tab */}
            {activeTab === "stats" && (
              <div className="grid grid-cols-2 gap-3 font-mono text-xs">
                <div className="bg-[#1e1e1e] border border-[#3c3c3c] p-3 rounded">
                  <div className="text-gray-400">Source Modules</div>
                  <div className="text-2xl font-bold text-white mt-1">{Object.keys(files).length}</div>
                </div>
                
                <div className="bg-[#1e1e1e] border border-[#3c3c3c] p-3 rounded">
                  <div className="text-gray-400">AST Node Allocation</div>
                  <div className="text-2xl font-bold text-[#4ec9b0] mt-1">{compilation?.metrics?.ast_nodes || 0}</div>
                </div>
                
                <div className="bg-[#1e1e1e] border border-[#3c3c3c] p-3 rounded">
                  <div className="text-gray-400">CFG Basic Chunks</div>
                  <div className="text-2xl font-bold text-[#dcdcaa] mt-1">{compilation?.metrics?.cfg_blocks || 0}</div>
                </div>
                
                <div className="bg-[#1e1e1e] border border-[#3c3c3c] p-3 rounded">
                  <div className="text-gray-400">Semantic Failures</div>
                  <div className="text-2xl font-bold text-red-400 mt-1">{compilation?.metrics?.errors || 0}</div>
                </div>
              </div>
            )}

          </div>
        </section>

      </div>
    </div>
  );
}