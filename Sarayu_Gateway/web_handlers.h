// Web Server Handlers

const char HTML_PAGE[] PROGMEM = R"rawliteral(<!doctype html>
<html lang="en">
<head>
<meta charset="UTF-8"/>
<meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>Sarayu Gateway — Network Setup</title>
<link rel="preconnect" href="https://fonts.googleapis.com"/>
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin/>
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&family=JetBrains+Mono:wght@500&display=swap" rel="stylesheet"/>
<style>
*,*::before,*::after{box-sizing:border-box;margin:0;padding:0}
:root{--bg:#07090f;--panel:rgba(17,22,34,0.72);--panel-solid:#111622;--field:rgba(255,255,255,0.04);--field-hover:rgba(255,255,255,0.07);--border:rgba(255,255,255,0.09);--border-strong:rgba(255,255,255,0.16);--accent:#8b5cf6;--accent-2:#ec4899;--accent-soft:rgba(139,92,246,0.16);--danger:#f87171;--success:#34d399;--text:#f4f6fb;--sub:#8b94a8;--muted:#5d667a;--radius:18px;--radius-sm:12px;--shadow:0 30px 80px -20px rgba(0,0,0,0.7);--font:"Inter",ui-sans-serif,system-ui,-apple-system,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif;--mono:"JetBrains Mono",ui-monospace,SFMono-Regular,Menlo,Consolas,monospace}
html{-webkit-text-size-adjust:100%}
body{font-family:var(--font);font-feature-settings:"cv11","ss01";-webkit-font-smoothing:antialiased;background:var(--bg);background-image:radial-gradient(ellipse 80% 50% at 50% -10%,rgba(139,92,246,0.22),transparent 60%),radial-gradient(ellipse 60% 40% at 100% 100%,rgba(236,72,153,0.1),transparent 60%);background-attachment:fixed;min-height:100vh;display:flex;align-items:center;justify-content:center;padding:2rem 1rem;color:var(--text);line-height:1.5}
body::before{content:"";position:fixed;inset:0;background-image:linear-gradient(rgba(255,255,255,0.025) 1px,transparent 1px),linear-gradient(90deg,rgba(255,255,255,0.025) 1px,transparent 1px);background-size:44px 44px;mask-image:radial-gradient(ellipse at center,#000 30%,transparent 75%);-webkit-mask-image:radial-gradient(ellipse at center,#000 30%,transparent 75%);pointer-events:none;z-index:0}
.layout{position:relative;z-index:1;display:grid;grid-template-columns:2fr minmax(380px,460px) 1fr;grid-template-rows:auto 1fr;gap:1.25rem;align-items:start;width:100%;max-width:1400px}
.layout > .side-left{grid-column:1;grid-row:1;justify-self:start;width:100%;margin-left:150px;max-width:250px}
.layout > .side-right{grid-column:1;grid-row:2;justify-self:start;width:100%;margin-left:150px;max-width:250px}
.layout > .main{grid-column:2;grid-row:1/span 2}
@media (max-width:1000px){
  .layout{grid-template-columns:1fr;grid-template-rows:auto;max-width:460px}
  .layout > .side-left,.layout > .side-right,.layout > .main{grid-column:1;grid-row:auto;justify-self:stretch;max-width:none;margin-left:0}
  .layout > .main{order:1}
  .layout > .side-left{order:2}
  .layout > .side-right{order:3}
}
.card{position:relative;background:var(--panel);backdrop-filter:blur(24px) saturate(140%);-webkit-backdrop-filter:blur(24px) saturate(140%);border:1px solid var(--border);border-radius:var(--radius);box-shadow:var(--shadow)}
.card.main{padding:2rem 1.9rem 1.9rem}
.card.side{padding:0.8rem 0.85rem}
.card.main::before{content:"";position:absolute;inset:0;border-radius:inherit;padding:1px;background:linear-gradient(160deg,rgba(139,92,246,0.55),transparent 35%,transparent 70%,rgba(236,72,153,0.35));-webkit-mask:linear-gradient(#000 0 0) content-box,linear-gradient(#000 0 0);-webkit-mask-composite:xor;mask-composite:exclude;pointer-events:none}
.logo{display:flex;align-items:center;gap:0.85rem;margin-bottom:1.4rem}
.logo-icon{width:46px;height:46px;border-radius:14px;background:linear-gradient(135deg,var(--accent),var(--accent-2));display:grid;place-items:center;box-shadow:0 8px 24px -4px rgba(139,92,246,0.55),inset 0 1px 0 rgba(255,255,255,0.35)}
.logo-icon svg{width:24px;height:24px;stroke:#fff}
.logo-text h1{font-size:1.15rem;font-weight:700;letter-spacing:-0.02em;line-height:1.2}
.logo-text span{font-size:0.78rem;color:var(--sub)}
.badge{display:inline-flex;align-items:center;gap:0.5rem;font-size:0.7rem;font-weight:600;letter-spacing:0.06em;text-transform:uppercase;padding:0.32rem 0.8rem;border-radius:999px;margin-bottom:1.5rem;background:rgba(52,211,153,0.1);color:var(--success);border:1px solid rgba(52,211,153,0.25)}
.badge-dot{width:6px;height:6px;border-radius:50%;background:currentColor;box-shadow:0 0 0 0 currentColor;animation:ping 1.8s ease-out infinite}
@keyframes ping{0%{box-shadow:0 0 0 0 rgba(52,211,153,0.6)}100%{box-shadow:0 0 0 9px rgba(52,211,153,0)}}
.section-label{font-size:0.7rem;font-weight:600;letter-spacing:0.12em;text-transform:uppercase;color:var(--muted);margin-bottom:0.75rem}
.field{margin-bottom:1rem}
.field label{display:block;font-size:0.8rem;font-weight:500;color:var(--sub);margin-bottom:0.45rem}
.input-wrap{position:relative}
.input-wrap input,.input-wrap select{width:100%;padding:0.75rem 0.95rem;background:var(--field);border:1px solid var(--border);border-radius:var(--radius-sm);color:var(--text);font-size:0.92rem;font-family:inherit;outline:none;transition:border-color 0.2s,box-shadow 0.2s,background 0.2s}
.input-wrap input::placeholder{color:var(--muted)}
.input-wrap input:hover,.input-wrap select:hover{background:var(--field-hover)}
.input-wrap input[type="password"],.input-wrap input.pw{padding-right:2.7rem}
#ip,#netmask,#gateway,#dns{font-family:var(--mono);font-size:0.86rem;letter-spacing:0.01em}
.input-wrap input:focus,.input-wrap select:focus{border-color:var(--accent);background:rgba(139,92,246,0.06);box-shadow:0 0 0 4px rgba(139,92,246,0.18)}
.input-wrap select{appearance:none;-webkit-appearance:none;cursor:pointer;background-image:url("data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='12' height='8' viewBox='0 0 12 8'><path d='M1 1.5l5 5 5-5' fill='none' stroke='%238b94a8' stroke-width='1.8' stroke-linecap='round' stroke-linejoin='round'/></svg>");background-repeat:no-repeat;background-position:right 14px center;padding-right:2.4rem}
.input-wrap select option{background:var(--panel-solid);color:var(--text)}
.eye-btn{position:absolute;right:0.55rem;top:50%;transform:translateY(-50%);width:32px;height:32px;border-radius:8px;background:none;border:none;cursor:pointer;color:var(--sub);display:grid;place-items:center;transition:color 0.2s,background 0.2s}
.eye-btn:hover{color:var(--text);background:var(--field-hover)}
.radio-group{display:flex;gap:0.25rem;padding:0.25rem;background:var(--field);border:1px solid var(--border);border-radius:var(--radius-sm);margin-bottom:1rem}
.radio-group label{flex:1;display:flex;align-items:center;justify-content:center;padding:0.55rem 0.4rem;border-radius:9px;color:var(--sub);font-size:0.8rem;font-weight:500;text-align:center;cursor:pointer;transition:background 0.2s,color 0.2s,box-shadow 0.2s;margin:0;user-select:none}
.radio-group input{position:absolute;opacity:0;pointer-events:none;width:0;height:0}
.radio-group label:hover{color:var(--text)}
.radio-group label:has(input:checked){background:linear-gradient(135deg,var(--accent),#7c3aed);color:#fff;box-shadow:0 4px 14px -2px rgba(139,92,246,0.55)}
.radio-group label:has(input:focus-visible){outline:2px solid var(--accent-2);outline-offset:2px}
.section{display:none;animation:fadeIn 0.3s ease}
@keyframes fadeIn{from{opacity:0;transform:translateY(6px)}to{opacity:1;transform:none}}
.divider{display:flex;align-items:center;gap:0.8rem;margin:1.5rem 0 1.1rem}
.divider::before,.divider::after{content:"";flex:1;height:1px;background:var(--border)}
.divider span{font-size:0.68rem;font-weight:600;color:var(--muted);white-space:nowrap;letter-spacing:0.12em;text-transform:uppercase}
.buttons{display:flex;flex-direction:column;gap:0.6rem;margin-top:1.6rem}
.btn{width:100%;padding:0.85rem;border:none;border-radius:var(--radius-sm);font-size:0.93rem;font-weight:600;font-family:inherit;cursor:pointer;display:flex;align-items:center;justify-content:center;gap:0.55rem;transition:transform 0.12s,box-shadow 0.2s,filter 0.2s,border-color 0.2s,color 0.2s,background 0.2s}
.btn:active{transform:scale(0.985)}
.btn:disabled{opacity:0.65;cursor:default}
.btn-primary{background:linear-gradient(135deg,var(--accent),#7c3aed 60%,#ec4899);color:#fff;box-shadow:0 10px 28px -8px rgba(139,92,246,0.7),inset 0 1px 0 rgba(255,255,255,0.25)}
.btn-primary:hover:not(:disabled){filter:brightness(1.1);box-shadow:0 14px 34px -8px rgba(139,92,246,0.85),inset 0 1px 0 rgba(255,255,255,0.25)}
.btn-ghost{background:transparent;border:1px solid var(--border-strong);color:var(--sub)}
.btn-ghost:hover:not(:disabled){background:var(--field);border-color:var(--danger);color:var(--danger)}
.spin{width:18px;height:18px;border:2.5px solid rgba(255,255,255,0.3);border-top-color:#fff;border-radius:50%;animation:spin 0.7s linear infinite;display:none}
@keyframes spin{to{transform:rotate(360deg)}}
#toast{position:fixed;top:1.2rem;left:50%;transform:translateX(-50%) translateY(-90px);z-index:999;background:var(--panel-solid);border:1px solid var(--border-strong);border-radius:999px;padding:0.7rem 1.3rem;font-size:0.85rem;font-weight:500;display:flex;align-items:center;gap:0.5rem;box-shadow:var(--shadow);transition:transform 0.4s cubic-bezier(0.34,1.56,0.64,1);pointer-events:none;max-width:92vw;text-align:center}
#toast.show{transform:translateX(-50%) translateY(0)}
#toast.success{color:var(--success);border-color:rgba(52,211,153,0.35)}
#toast.error{color:var(--danger);border-color:rgba(248,113,113,0.35)}
#toast.info{color:#c4b5fd;border-color:rgba(139,92,246,0.4)}
.status-head{display:flex;justify-content:space-between;align-items:center;margin-bottom:0.6rem}
.side-title{display:flex;align-items:center;gap:0.5rem;font-size:0.72rem;font-weight:600;letter-spacing:0.12em;text-transform:uppercase;color:var(--text)}
.side-title::before{content:"";width:7px;height:7px;border-radius:50%;background:var(--success);box-shadow:0 0 10px var(--success)}
.side-right .side-title::before{background:var(--muted);box-shadow:none}
.refresh-btn{background:var(--field);border:1px solid var(--border);color:var(--sub);border-radius:8px;font-size:0.72rem;font-weight:500;padding:0.3rem 0.7rem;cursor:pointer;font-family:inherit;transition:all 0.2s}
.refresh-btn:hover{border-color:var(--accent);color:#c4b5fd;background:var(--accent-soft)}
.status-card{background:rgba(0,0,0,0.22);border:1px solid var(--border);border-radius:var(--radius-sm);padding:0.2rem 0.65rem}
.srow{display:flex;justify-content:space-between;align-items:baseline;gap:0.6rem;font-size:0.78rem;padding:0.4rem 0;border-bottom:1px dashed var(--border)}
.srow:last-child{border-bottom:none}
.srow span:first-child{color:var(--sub);flex-shrink:0}
.srow span:last-child{font-family:var(--mono);font-size:0.76rem;font-weight:500;color:var(--text);word-break:break-all;text-align:right}
.status-empty{font-size:0.82rem;color:var(--sub);padding:0.6rem 0}
@media (max-width:480px){body{padding:1rem 0.75rem}.card.main{padding:1.6rem 1.25rem}.radio-group label{font-size:0.74rem}}
@media (prefers-reduced-motion:reduce){*,*::before,*::after{animation:none !important;transition:none !important}}
</style>
</head>
<body>
<div id="toast"></div>
<div class="layout">
<div class="card side side-left">
<div class="status-head">
<div class="side-title">Current</div>
<button type="button" class="refresh-btn" onclick="loadStatus()">Refresh</button>
</div>
<div class="status-card">
<div id="statusCurrent" class="status-empty">Loading&#8230;</div>
</div>
</div>
<div class="card main">
<div class="logo">
<div class="logo-icon">
<svg viewBox="0 0 24 24" fill="none" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
<path d="M5 12.55a11 11 0 0 1 14.08 0"/>
<path d="M1.42 9a16 16 0 0 1 21.16 0"/>
<path d="M8.53 16.11a6 6 0 0 1 6.95 0"/>
<line x1="12" y1="20" x2="12.01" y2="20"/>
</svg>
</div>
<div class="logo-text">
<h1>Sarayu Gateway</h1>
<span>Network configuration portal</span>
</div>
</div>
<div class="badge">
<span class="badge-dot"></span>
Setup mode active
</div>
<form id="networkForm" onsubmit="return false;">
<div class="section-label">Network mode</div>
<div class="field">
<label for="mode">How should this gateway connect?</label>
<div class="input-wrap">
<select id="mode" onchange="updateMode()">
<option value="wifi">Wi-Fi</option>
<option value="ethernet">Ethernet</option>
<option value="both">Wi-Fi + Ethernet</option>
</select>
</div>
</div>
<div id="wifiSection" class="section">
<div class="divider"><span>Wi-Fi network</span></div>
<div class="field">
<label for="ssid">Network SSID</label>
<div class="input-wrap">
<input type="text" id="ssid" placeholder="Enter Wi-Fi SSID" autocomplete="off"/>
</div>
</div>
<div class="radio-group">
<label>
<input type="radio" name="security" value="closed" checked onchange="updateSecurity()"/>
Password protected
</label>
<label>
<input type="radio" name="security" value="open" onchange="updateSecurity()"/>
Open network
</label>
</div>
<div id="passwordSection" class="field">
<label for="password">Password</label>
<div class="input-wrap">
<input type="password" id="password" placeholder="Enter password" autocomplete="off"/>
<button type="button" class="eye-btn" onclick="toggleEye('password','pwEye')" title="Show/hide">
<svg id="pwEye" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
<path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/>
<circle cx="12" cy="12" r="3"/>
</svg>
</button>
</div>
</div>
</div>
<div id="ethernetSection" class="section">
<div class="divider"><span>Ethernet</span></div>
<div class="radio-group">
<label>
<input type="radio" name="ipmode" value="dhcp" checked onchange="updateIPMode()"/>
Dynamic IP (DHCP)
</label>
<label>
<input type="radio" name="ipmode" value="static" onchange="updateIPMode()"/>
Static IP
</label>
</div>
<div id="staticSection">
<div class="field">
<label for="ip">IP address</label>
<div class="input-wrap"><input type="text" id="ip" placeholder="192.168.1.100"/></div>
</div>
<div class="field">
<label for="netmask">Subnet mask</label>
<div class="input-wrap"><input type="text" id="netmask" placeholder="255.255.255.0"/></div>
</div>
<div class="field">
<label for="gateway">Gateway</label>
<div class="input-wrap"><input type="text" id="gateway" placeholder="192.168.1.1"/></div>
</div>
<div class="field">
<label for="dns">DNS</label>
<div class="input-wrap"><input type="text" id="dns" placeholder="8.8.8.8"/></div>
</div>
</div>
</div>
<div id="prioritySection" class="section">
<div class="divider"><span>Network priority</span></div>
<div class="field">
<label for="priority">Which connection should this gateway prefer?</label>
<div class="input-wrap">
<select id="priority">
<option value="wifi_first">Wi-Fi &#8594; Ethernet</option>
<option value="ethernet_first">Ethernet &#8594; Wi-Fi</option>
</select>
</div>
</div>
</div>
<div class="buttons">
<button type="button" class="btn btn-primary" id="saveBtn" onclick="saveConfiguration()">
<svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round">
<path d="M5 12.55a11 11 0 0 1 14.08 0"/>
<path d="M1.42 9a16 16 0 0 1 21.16 0"/>
<path d="M8.53 16.11a6 6 0 0 1 6.95 0"/>
<line x1="12" y1="20" x2="12.01" y2="20"/>
</svg>
<span id="saveBtnText">Save &amp; Connect</span>
<div class="spin" id="saveSpin"></div>
</button>
<button type="button" class="btn btn-ghost" id="cancelBtn" onclick="cancelConfiguration()">
<span id="cancelBtnText">Cancel</span>
<div class="spin" id="cancelSpin"></div>
</button>
</div>
</form>
</div>
<div class="card side side-right">
<div class="status-head">
<div class="side-title">Previous</div>
</div>
<div class="status-card">
<div id="statusPrevious" class="status-empty">Loading&#8230;</div>
</div>
</div>
</div>
<script>
function $(id){return document.getElementById(id)}
function toast(msg,type,dur){var t=$('toast');t.className='';t.innerHTML=msg;void t.offsetWidth;t.className=type+' show';clearTimeout(t._t);t._t=setTimeout(function(){t.className=type},dur||3000)}
function toggleEye(inputId,svgId){var inp=$(inputId),svg=$(svgId);if(inp.type==='password'){inp.type='text';svg.innerHTML='<path d="M17.94 17.94A10.07 10.07 0 0 1 12 20c-7 0-11-8-11-8a18.45 18.45 0 0 1 5.06-5.94"/><path d="M9.9 4.24A9.12 9.12 0 0 1 12 4c7 0 11 8 11 8a18.5 18.5 0 0 1-2.16 3.19"/><line x1="1" y1="1" x2="23" y2="23"/>'}else{inp.type='password';svg.innerHTML='<path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/>'}}
function setLoading(btn,spin,text,label,state){$(btn).disabled=state;$(spin).style.display=state?'block':'none';$(text).style.display=state?'none':'inline';if(!state&&label)$(text).innerHTML=label}
function updateMode(){const mode=$("mode").value;$("wifiSection").style.display=(mode==="wifi"||mode==="both")?"block":"none";$("ethernetSection").style.display=(mode==="ethernet"||mode==="both")?"block":"none";$("prioritySection").style.display=mode==="both"?"block":"none"}
function updateSecurity(){const security=document.querySelector('input[name="security"]:checked').value;$("passwordSection").style.display=security==="closed"?"block":"none"}
function updateIPMode(){const ipmode=document.querySelector('input[name="ipmode"]:checked').value;$("staticSection").style.display=ipmode==="static"?"block":"none"}
function saveConfiguration(){const mode=$("mode").value;const ssid=$("ssid").value.trim();const security=document.querySelector('input[name="security"]:checked').value;const password=$("password").value;const ipmode=document.querySelector('input[name="ipmode"]:checked').value;const ip=$("ip").value.trim();const netmask=$("netmask").value.trim();const gateway=$("gateway").value.trim();const dns=$("dns").value.trim();const priority=$("priority").value;if(mode==="wifi"||mode==="both"){if(!ssid){toast("&#x26A0; Please enter Wi-Fi SSID","error");return}if(security==="closed"&&password.length<8){toast("&#x26A0; Wi-Fi password must contain at least 8 characters","error");return}}if((mode==="ethernet"||mode==="both")&&ipmode==="static"){if(!ip||!netmask||!gateway||!dns){toast("&#x26A0; Please fill all static Ethernet fields","error");return}}const config={mode:mode,priority:priority,timeout:20,wifi:{ssid:ssid,security:security,password:password},ethernet:{ip_mode:ipmode,ip:ip,netmask:netmask,gateway:gateway,dns:dns}};setLoading('saveBtn','saveSpin','saveBtnText',null,true);toast("Applying network configuration&#8230;","info",4000);fetch("/save",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify(config)}).then(response=>response.json()).then(data=>{setLoading('saveBtn','saveSpin','saveBtnText','Save & Connect',false);if(data.success){toast("&#x2705; Configuration saved &#8212; applying network settings&#8230;","success",5000);setTimeout(loadStatus,8000)}else{toast("&#x274C; "+data.message,"error",5000)}}).catch(error=>{console.error(error);setLoading('saveBtn','saveSpin','saveBtnText','Save & Connect',false);toast("Network change started &#8212; connection may temporarily disconnect.","info",5000)})}
function cancelConfiguration(){const confirmCancel=confirm("Cancel configuration and return to the current network settings?");if(!confirmCancel)return;setLoading('cancelBtn','cancelSpin','cancelBtnText',null,true);toast("Restoring current network configuration&#8230;","info",4000);fetch("/cancel",{method:"POST"}).then(response=>response.json()).then(data=>{setLoading('cancelBtn','cancelSpin','cancelBtnText','Cancel',false);if(data.success){toast("&#x2705; Current configuration restored.","success",4000);setTimeout(loadStatus,8000)}else{toast("&#x274C; "+data.message,"error",5000)}}).catch(error=>{console.error(error);setLoading('cancelBtn','cancelSpin','cancelBtnText','Cancel',false);toast("Restoring current network &#8212; connection may disconnect.","info",4000)})}
function renderStatus(id,cfg){const box=$(id);box.innerHTML='';if(!cfg){box.className='status-empty';box.textContent='Not available';return}if(cfg.error){box.className='status-empty';box.textContent='Error: '+cfg.error;return}box.className='';const rows=[['Mode',cfg.mode]];const wifi=cfg.wifi||{},eth=cfg.ethernet||{};if(cfg.mode==='both')rows.push(['Priority',cfg.priority]);if(cfg.mode==='wifi'||cfg.mode==='both'){rows.push(['Wi-Fi SSID',wifi.ssid||'-']);rows.push(['Security',wifi.security]);if(wifi.security==='closed')rows.push(['Password',wifi.password||'-'])}if(cfg.mode==='ethernet'||cfg.mode==='both'){rows.push(['IP mode',eth.ip_mode]);if(eth.ip_mode==='static'){rows.push(['IP',eth.ip],['Netmask',eth.netmask],['Gateway',eth.gateway],['DNS',eth.dns])}}rows.forEach(function(r){const d=document.createElement('div');d.className='srow';const a=document.createElement('span');a.textContent=r[0];const b=document.createElement('span');b.textContent=(r[1]===undefined||r[1]==='')?'-':r[1];d.appendChild(a);d.appendChild(b);box.appendChild(d)})}
function loadStatus(){fetch('/status').then(r=>r.json()).then(d=>{renderStatus('statusCurrent',d.current);renderStatus('statusPrevious',d.previous)}).catch(()=>{$('statusCurrent').textContent='Could not load status';$('statusPrevious').textContent='Could not load status'})}
updateMode();updateSecurity();updateIPMode();loadStatus();
</script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

void handleSave() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, body);
    
    if (error) {
      server.send(400, "application/json", "{\"success\":false,\"message\":\"Invalid JSON\"}");
      return;
    }
    
    // Update configuration
    currentConfig.mode = doc["mode"].as<String>();
    currentConfig.priority = doc["priority"].as<String>();
    currentConfig.timeout = doc["timeout"] | 20;
    
    currentConfig.wifi_ssid = doc["wifi"]["ssid"].as<String>();
    currentConfig.wifi_security = doc["wifi"]["security"].as<String>();
    currentConfig.wifi_password = doc["wifi"]["password"].as<String>();
    
    currentConfig.eth_ip_mode = doc["ethernet"]["ip_mode"].as<String>();
    currentConfig.eth_ip = doc["ethernet"]["ip"].as<String>();
    currentConfig.eth_netmask = doc["ethernet"]["netmask"].as<String>();
    currentConfig.eth_gateway = doc["ethernet"]["gateway"].as<String>();
    currentConfig.eth_dns = doc["ethernet"]["dns"].as<String>();
    
    // Save to NVS
    saveConfiguration();
    
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Configuration saved\"}");
    
    // Apply configuration after response sent
    delay(500);
    applyNetworkConfiguration();
  } else {
    server.send(400, "application/json", "{\"success\":false,\"message\":\"No data received\"}");
  }
}

void handleCancel() {
  // Restore previous configuration (if exists)
  if (previousConfig.mode.length() > 0) {
    currentConfig = previousConfig;
    saveConfiguration();
    applyNetworkConfiguration();
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Configuration restored\"}");
  } else {
    server.send(200, "application/json", "{\"success\":false,\"message\":\"No previous configuration\"}");
  }
}

void handleStatus() {
  StaticJsonDocument<2048> doc;
  
  // Current configuration
  JsonObject current = doc.createNestedObject("current");
  current["mode"] = currentConfig.mode;
  current["priority"] = currentConfig.priority;
  
  JsonObject currentWifi = current.createNestedObject("wifi");
  currentWifi["ssid"] = currentConfig.wifi_ssid;
  currentWifi["security"] = currentConfig.wifi_security;
  currentWifi["password"] = currentConfig.wifi_password;
  
  JsonObject currentEth = current.createNestedObject("ethernet");
  currentEth["ip_mode"] = currentConfig.eth_ip_mode;
  currentEth["ip"] = currentConfig.eth_ip;
  currentEth["netmask"] = currentConfig.eth_netmask;
  currentEth["gateway"] = currentConfig.eth_gateway;
  currentEth["dns"] = currentConfig.eth_dns;
  
  // Previous configuration
  if (previousConfig.mode.length() > 0) {
    JsonObject previous = doc.createNestedObject("previous");
    previous["mode"] = previousConfig.mode;
    previous["priority"] = currentConfig.priority;
    
    JsonObject prevWifi = previous.createNestedObject("wifi");
    prevWifi["ssid"] = previousConfig.wifi_ssid;
    prevWifi["security"] = previousConfig.wifi_security;
    
    JsonObject prevEth = previous.createNestedObject("ethernet");
    prevEth["ip_mode"] = previousConfig.eth_ip_mode;
  }
  
  String response;
  serializeJson(doc, response);
  server.send(200, "application/json", response);
}
