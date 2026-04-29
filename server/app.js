const express = require('express');
const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs');
const cors = require('cors');

const app = express();
const PORT = 3000;

app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

const OPTIVERSE_BINARY = path.join(__dirname, '..', 'optiverse.exe');

const MODULES = {
  1: { name:'Smart Event Scheduling', description:'Select max non-overlapping events. Greedy vs Brute Force.', badge:'Greedy', complexity:{ brute:'O(2ⁿ · n log n)', optimized:'O(n log n)' } },
  2: { name:'Traffic Flow Analyzer',  description:'Max traffic in window k. Sliding Window vs Brute Force.',  badge:'Sliding Window', complexity:{ brute:'O(n·k)', optimized:'O(n)' } },
  3: { name:'Load Balancing Optimizer',description:'Minimize max workload across workers. Binary Search vs Naive.', badge:'Binary Search', complexity:{ brute:'O(n²)', optimized:'O(n log S)' } },
  4: { name:'Fast Range Query System',description:'Answer range sum queries. Prefix Sum vs Brute Force.',    badge:'Prefix Sum', complexity:{ brute:'O(n) per query', optimized:'O(1) per query' } },
  5: { name:'Secure Data Processing', description:'GCD, Prime, or XOR range queries. Optimized vs Brute.', badge:'Number Theory', complexity:{ brute:'O(n)', optimized:'O(log n)' } },
  6: { name:'Game Strategy Analyzer', description:'Win/Lose position in Nim-variant via Grundy numbers.',   badge:'Game Theory', complexity:{ brute:'O(n·m)', optimized:'O(n)' } },
  7: { name:'Network Dependency Resolver',description:'Resolve dependencies, detect cycles. Kahn\'s Topo Sort.', badge:'Graph', complexity:{ brute:'O(V+E)', optimized:'O(V+E)' } },
  8: { name:'Hierarchical Query System',  description:'LCA queries on trees. Binary Lifting vs Brute Force.', badge:'Tree / LCA', complexity:{ brute:'O(n) per query', optimized:'O(log n) per query' } }
};

function runBinary(input) {
  return new Promise((resolve, reject) => {
    if (!fs.existsSync(OPTIVERSE_BINARY)) return resolve({ stdout:'__BINARY_NOT_FOUND__', stderr:'' });
    const child = spawn(OPTIVERSE_BINARY, [], { timeout: 15000 });
    let stdout = '', stderr = '';
    child.stdin.write(input);
    child.stdin.end();
    child.stdout.on('data', d => { if (stdout.length < 30000) stdout += d.toString(); });
    child.stderr.on('data', d => { stderr += d.toString(); });
    child.on('close', () => resolve({ stdout, stderr }));
    child.on('error', err => reject(err));
  });
}

function buildInput(mid, body) {
  let input = `${mid}\ny\n`;
  switch (mid) {
    case 1: {
      const events = body.events || [];
      input += `${events.length}\n`;
      events.forEach(e => { input += `${e.start} ${e.end}\n`; });
      break;
    }
    case 2: {
      const arr = body.traffic || []; const k = body.k || 3;
      input += `${arr.length}\n${arr.join(' ')}\n${k}\n`;
      break;
    }
    case 3: {
      const tasks = body.tasks || []; const workers = body.workers || 2;
      input += `${tasks.length}\n${tasks.join(' ')}\n${workers}\n`;
      break;
    }
    case 4: {
      const arr = body.arr || []; const queries = body.queries || [];
      input += `${arr.length}\n${arr.join(' ')}\n${queries.length}\n`;
      queries.forEach(q => { input += `${q.l} ${q.r}\n`; });
      break;
    }
    case 5: {
      const subOp = parseInt(body.subOp) || 1;
      input += `${subOp}\n`;
      if (subOp === 1) input += `${body.a || 12} ${body.b || 8}\n`;
      else if (subOp === 2) input += `${body.n || 17}\n`;
      else input += `${body.L || 1} ${body.R || 10}\n`;
      break;
    }
    case 6: {
      const piles = body.piles || [];
      input += `${piles.length}\n${piles.join(' ')}\n`;
      break;
    }
    case 7: {
      const nodes = body.nodes || 4; const edges = body.edges || [];
      input += `${nodes} ${edges.length}\n`;
      edges.forEach(e => { input += `${e.u} ${e.v}\n`; });
      break;
    }
    case 8: {
      const nodes = body.nodes || 5; const edges = body.edges || []; const queries = body.queries || [];
      input += `${nodes}\n`;
      edges.forEach(e => { input += `${e.u} ${e.v}\n`; });
      input += `${queries.length}\n`;
      queries.forEach(q => { input += `${q.u} ${q.v}\n`; });
      break;
    }
    default: input += '\n';
  }
  input += `0\n`;
  return input;
}

function parseOutput(stdout, mid) {
  if (stdout === '__BINARY_NOT_FOUND__') return { raw:'⚠ Binary not found. Compile optiverse.exe in OPTIVERSE/ folder.', bruteMs:null, optiMs:null, speedup:null };
  const cleaned = stdout.replace(/\r\n/g,'\n').replace(/\r/g,'\n');
  const bruteMatch = cleaned.match(/[Bb]rute[^:\n]*:\s*([\d.]+)\s*(ms|microseconds|sec|us)/);
  const optiMatch  = cleaned.match(/(Optimized|Greedy|Sliding|Prefix)[^:\n]*:\s*([\d.]+)\s*(ms|microseconds|sec|us)/);
  const speedMatch = cleaned.match(/[Ss]peedup[^:\n]*:\s*([\d.]+)x/);
  let bruteMs = null, optiMs = null, speedup = null;
  const toMs = (v, u) => u==='microseconds'||u==='us' ? v/1000 : u==='sec' ? v*1000 : v;
  if (bruteMatch) bruteMs = toMs(parseFloat(bruteMatch[1]), bruteMatch[2]);
  if (optiMatch)  optiMs  = toMs(parseFloat(optiMatch[2]),  optiMatch[3]);
  if (speedMatch) speedup = parseFloat(speedMatch[1]);
  if (bruteMs !== null && optiMs !== null && optiMs > 0 && !speedup) speedup = bruteMs / optiMs;
  return { raw: cleaned, bruteMs, optiMs, speedup: speedup ? parseFloat(speedup.toFixed(2)) : null };
}

app.get('/api/status', (req, res) => {
  res.json({ server:'running', binaryFound: fs.existsSync(OPTIVERSE_BINARY), mode: fs.existsSync(OPTIVERSE_BINARY)?'live':'demo' });
});

app.get('/api/modules', (req, res) => {
  res.json({ modules: MODULES });
});

app.post('/api/run', async (req, res) => {
  const mid = parseInt(req.body.moduleId);
  if (!mid || !MODULES[mid]) return res.status(400).json({ success:false, error:'Invalid module ID' });
  try {
    const input = buildInput(mid, req.body);
    const output = await runBinary(input);
    const parsed = parseOutput(output.stdout, mid);
    res.json({ success:true, module: MODULES[mid].name, raw: parsed.raw, bruteMs: parsed.bruteMs, optiMs: parsed.optiMs, speedup: parsed.speedup, complexity: MODULES[mid].complexity });
  } catch (err) {
    res.status(500).json({ success:false, error: err.toString() });
  }
});

app.use((req, res) => { res.sendFile(path.join(__dirname, 'public', 'index.html')); });

app.listen(PORT, () => {
  console.log(`OptiVerse server → http://localhost:${PORT}`);
  console.log(`Binary: ${fs.existsSync(OPTIVERSE_BINARY) ? 'FOUND ✓' : 'NOT FOUND (demo mode)'}`);
});