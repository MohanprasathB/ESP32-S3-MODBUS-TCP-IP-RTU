// Web Server Handlers
// HTML stored in Flash memory (PROGMEM) to save RA

#pragma once
#include <pgmspace.h>

const char GATEWAY_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Sarayu Gateway — Configuration</title>
<style>
*,*::before,*::after{box-sizing:border-box;margin:0;padding:0}
:root{
  --bg:#0f172a;
  --surface:#1e293b;
  --surface2:#273449;
  --border:#334155;
  --accent:#3b82f6;
  --accent-h:#2563eb;
  --danger:#ef4444;
  --success:#22c55e;
  --warn:#f59e0b;
  --text:#f1f5f9;
  --sub:#94a3b8;
  --radius:14px;
  --shadow:0 24px 60px rgba(0,0,0,.55);
}
html{color-scheme:dark}
body{
  font-family:'Segoe UI',system-ui,sans-serif;
  background:var(--bg);
  min-height:100vh;
  display:flex;
  align-items:flex-start;
  justify-content:center;
  padding:1.5rem 1rem 2.5rem;
  color:var(--text);
}
 
.orb{position:fixed;border-radius:50%;filter:blur(80px);opacity:.18;pointer-events:none;z-index:0}
.orb1{width:520px;height:520px;background:#3b82f6;top:-120px;left:-120px;animation:drift1 12s ease-in-out infinite alternate}
.orb2{width:400px;height:400px;background:#8b5cf6;bottom:-100px;right:-100px;animation:drift2 15s ease-in-out infinite alternate}
.orb3{width:300px;height:300px;background:#06b6d4;bottom:30%;left:50%;animation:drift3 10s ease-in-out infinite alternate}
@keyframes drift1{to{transform:translate(60px,80px)}}
@keyframes drift2{to{transform:translate(-40px,-60px)}}
@keyframes drift3{to{transform:translate(-80px,40px)}}
@media (prefers-reduced-motion:reduce){.orb,.badge-dot,.spin{animation:none}}
 
/* ---------- layout ---------- */
.layout{
  position:relative;z-index:1;
  display:flex;align-items:flex-start;justify-content:center;
  gap:1.5rem;width:100%;max-width:1180px;
}
.layout > .main{flex:1 1 540px;max-width:540px;order:2}
.layout > .side{flex:1 1 280px;max-width:280px;padding:1.5rem 1.2rem;position:sticky;top:1.5rem}
.layout > .side-left{order:1}
.layout > .side-right{order:3}
 
@media (max-width:1060px){
  .layout{flex-direction:column;align-items:center}
  .layout > .main{order:1}
  .layout > .side-left{order:2}
  .layout > .side-right{order:3}
  .layout > .main,.layout > .side{width:100%;max-width:540px;flex:none;position:static}
}
 
.card{
  position:relative;z-index:1;
  background:rgba(30,41,59,.85);
  backdrop-filter:blur(18px);-webkit-backdrop-filter:blur(18px);
  border:1px solid var(--border);
  border-radius:var(--radius);
  padding:2.1rem 2rem;
  width:100%;
  box-shadow:var(--shadow);
}
@media (max-width:480px){.card{padding:1.6rem 1.2rem}}
 
/* ---------- header ---------- */
.logo{display:flex;align-items:center;gap:.7rem;margin-bottom:1.3rem}
.logo-icon{
  width:44px;height:44px;border-radius:10px;
  background:linear-gradient(135deg,#3b82f6,#8b5cf6);
  display:flex;align-items:center;justify-content:center;font-size:1.3rem;
  box-shadow:0 4px 16px rgba(59,130,246,.4);
}
.logo-text h1{font-size:1.1rem;font-weight:700;line-height:1.1}
.logo-text span{font-size:.75rem;color:var(--sub)}
 
.badge{
  display:inline-flex;align-items:center;gap:.4rem;
  font-size:.72rem;font-weight:600;letter-spacing:.04em;text-transform:uppercase;
  padding:.25rem .7rem;border-radius:999px;margin-bottom:1.3rem;
  background:rgba(59,130,246,.15);color:var(--accent);border:1px solid rgba(59,130,246,.3);
}
.badge-dot{width:6px;height:6px;border-radius:50%;background:currentColor;animation:pulse 1.4s ease-in-out infinite}
@keyframes pulse{0%,100%{opacity:1}50%{opacity:.3}}
 
/* ---------- tabs ---------- */
.tabs{
  display:grid;grid-template-columns:repeat(4,1fr);gap:.3rem;
  padding:.3rem;margin-bottom:1.5rem;
  background:var(--surface2);border:1px solid var(--border);border-radius:10px;
}
.tab{
  display:flex;align-items:center;justify-content:center;gap:.4rem;
  padding:.55rem .3rem;border:none;border-radius:7px;
  background:transparent;color:var(--sub);
  font:600 .8rem inherit;font-family:inherit;cursor:pointer;
  transition:background .2s,color .2s,box-shadow .2s;
}
.tab svg{flex:none}
.tab:hover{color:var(--text)}
.tab[aria-selected="true"]{
  background:linear-gradient(135deg,#3b82f6,#2563eb);color:#fff;
  box-shadow:0 3px 12px rgba(59,130,246,.35);
}
.tab:focus-visible,.btn:focus-visible,.dz:focus-visible,.eye-btn:focus-visible{outline:2px solid var(--accent);outline-offset:2px}
@media (max-width:420px){.tab span{display:none}}
 
.panel{display:none}
.panel.on{display:block}
 
/* ---------- form ---------- */
.section-label{
  font-size:.7rem;font-weight:700;letter-spacing:.1em;
  text-transform:uppercase;color:var(--sub);margin-bottom:1rem;
}
.field{margin-bottom:1rem}
.field label,.field .lab{display:block;font-size:.8rem;font-weight:600;color:var(--sub);margin-bottom:.4rem}
.input-wrap{position:relative}
.input-wrap input,.input-wrap select{
  width:100%;padding:.7rem .9rem;
  background:var(--surface2);border:1.5px solid var(--border);
  border-radius:8px;color:var(--text);font-size:.95rem;
  outline:none;transition:border-color .2s,box-shadow .2s;font-family:inherit;
}
.input-wrap input[type=password]{padding-right:2.6rem}
.input-wrap input:focus,.input-wrap select:focus{border-color:var(--accent);box-shadow:0 0 0 3px rgba(59,130,246,.18)}
.input-wrap input.invalid,.input-wrap select.invalid{border-color:var(--danger);box-shadow:0 0 0 3px rgba(239,68,68,.15)}
.input-wrap input:disabled,.input-wrap input[readonly],.input-wrap select:disabled{opacity:.65;cursor:not-allowed}
.input-wrap input::placeholder{color:#64748b}
.input-wrap select{
  appearance:none;-webkit-appearance:none;cursor:pointer;
  background-image:url("data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='10' height='6'><path d='M0 0l5 6 5-6z' fill='%2394a3b8'/></svg>");
  background-repeat:no-repeat;background-position:right 12px center;padding-right:30px;
}
.input-wrap select option{background:var(--surface);color:var(--text)}
.eye-btn{
  position:absolute;right:.7rem;top:50%;transform:translateY(-50%);
  background:none;border:none;cursor:pointer;color:var(--sub);
  display:flex;align-items:center;padding:0;transition:color .2s;
}
.eye-btn:hover{color:var(--text)}
.hint{font-size:.74rem;color:var(--sub);margin-top:.4rem;line-height:1.45}
.err-text{font-size:.74rem;color:var(--danger);margin-top:.4rem;display:none}
.err-text.show{display:block}
 
.radio-group{display:flex;gap:.6rem;margin-bottom:1rem}
.radio-group label{
  flex:1;display:flex;align-items:center;justify-content:center;gap:.4rem;
  padding:.6rem .5rem;border:1.5px solid var(--border);border-radius:8px;
  background:var(--surface2);color:var(--sub);font-size:.82rem;font-weight:600;
  cursor:pointer;transition:border-color .2s,color .2s;margin:0;
}
.radio-group input{width:auto;margin:0;accent-color:var(--accent)}
.radio-group label:has(input:checked){border-color:var(--accent);color:var(--text)}
.radio-group label:has(input:focus-visible){outline:2px solid var(--accent);outline-offset:2px}
 
/* selectable option cards (server security) */
.opt-grid{display:grid;grid-template-columns:1fr 1fr;gap:.6rem;margin-bottom:1rem}
.opt{
  display:flex;flex-direction:column;gap:.15rem;position:relative;
  padding:.7rem .8rem .7rem 2.2rem;border:1.5px solid var(--border);border-radius:10px;
  background:var(--surface2);cursor:pointer;transition:border-color .2s,background .2s;margin:0;
}
.opt input{position:absolute;left:.8rem;top:.85rem;margin:0;accent-color:var(--accent);width:auto}
.opt b{font-size:.84rem;color:var(--text);font-weight:600}
.opt small{font-size:.72rem;color:var(--sub);font-weight:500}
.opt:hover{border-color:#475569}
.opt:has(input:checked){border-color:var(--accent);background:rgba(59,130,246,.1)}
.opt:has(input:focus-visible){outline:2px solid var(--accent);outline-offset:2px}
@media (max-width:420px){.opt-grid{grid-template-columns:1fr}}
 
.section{display:none}
 
.divider{display:flex;align-items:center;gap:.8rem;margin:1.4rem 0}
.divider::before,.divider::after{content:'';flex:1;height:1px;background:var(--border)}
.divider span{font-size:.72rem;color:var(--sub);white-space:nowrap;letter-spacing:.06em;text-transform:uppercase}
 
.adv{margin-bottom:1rem;border:1px solid var(--border);border-radius:8px;background:rgba(39,52,73,.45)}
.adv summary{
  cursor:pointer;padding:.65rem .9rem;font-size:.8rem;font-weight:600;color:var(--sub);
  list-style:none;display:flex;justify-content:space-between;align-items:center;
}
.adv summary::-webkit-details-marker{display:none}
.adv summary::after{content:'+';font-size:1rem;line-height:1}
.adv[open] summary::after{content:'\2212'}
.adv summary:hover{color:var(--text)}
.adv-body{padding:.2rem .9rem .5rem}
 
/* toggle switch (Modbus enable) */
.switch-row{
  display:flex;align-items:center;justify-content:space-between;gap:1rem;
  padding:.8rem .9rem;margin-bottom:1rem;
  background:var(--surface2);border:1.5px solid var(--border);border-radius:10px;
}
.switch-row b{display:block;font-size:.9rem;font-weight:600}
.switch-row small{display:block;font-size:.74rem;color:var(--sub);margin-top:.1rem}
.switch{position:relative;width:44px;height:24px;flex:none}
.switch input{position:absolute;inset:0;opacity:0;cursor:pointer;margin:0;z-index:1}
.switch i{
  position:absolute;inset:0;border-radius:999px;background:#475569;transition:background .2s;
}
.switch i::after{
  content:'';position:absolute;top:3px;left:3px;width:18px;height:18px;border-radius:50%;
  background:#fff;transition:transform .2s;box-shadow:0 1px 3px rgba(0,0,0,.4);
}
.switch input:checked + i{background:var(--accent)}
.switch input:checked + i::after{transform:translateX(20px)}
.switch input:focus-visible + i{outline:2px solid var(--accent);outline-offset:2px}
 
/* ---------- dropzone ---------- */
.dz{
  display:flex;align-items:center;gap:.8rem;
  padding:.75rem .9rem;border:1.5px dashed var(--border);border-radius:10px;
  background:var(--surface2);cursor:pointer;
  transition:border-color .2s,background .2s;
}
.dz:hover,.dz.drag{border-color:var(--accent);background:rgba(59,130,246,.08)}
.dz.ok{border-style:solid;border-color:rgba(34,197,94,.55);background:rgba(34,197,94,.07)}
.dz.err{border-color:rgba(239,68,68,.65);background:rgba(239,68,68,.07)}
.dz-ico{
  width:36px;height:36px;border-radius:8px;flex:none;
  display:flex;align-items:center;justify-content:center;
  background:rgba(59,130,246,.15);color:var(--accent);
}
.dz.ok .dz-ico{background:rgba(34,197,94,.15);color:var(--success)}
.dz.err .dz-ico{background:rgba(239,68,68,.15);color:var(--danger)}
.dz-txt{flex:1;min-width:0}
.dz-title{font-size:.86rem;font-weight:600;white-space:nowrap;overflow:hidden;text-overflow:ellipsis}
.dz-sub{font-size:.72rem;color:var(--sub);margin-top:.1rem;line-height:1.35}
.dz.err .dz-sub{color:#fca5a5}
.dz.ok .dz-sub{color:#86efac}
.dz-clear{
  display:none;flex:none;width:26px;height:26px;border-radius:6px;
  background:transparent;border:1px solid var(--border);color:var(--sub);
  cursor:pointer;font-size:1rem;line-height:1;
}
.dz-clear:hover{color:var(--danger);border-color:var(--danger)}
.dz.ok .dz-clear,.dz.err .dz-clear{display:block}
.dz input[type=file]{display:none}
 
/* progress */
.progress{height:8px;border-radius:999px;background:var(--surface2);border:1px solid var(--border);overflow:hidden}
.progress > div{height:100%;width:0;border-radius:inherit;background:linear-gradient(90deg,#3b82f6,#8b5cf6);transition:width .15s linear}
.progress-meta{display:flex;justify-content:space-between;font-size:.74rem;color:var(--sub);margin-top:.45rem}
 
.notice{
  display:flex;gap:.6rem;padding:.7rem .85rem;margin-bottom:1rem;
  border-radius:8px;font-size:.78rem;line-height:1.45;
  background:rgba(245,158,11,.1);border:1px solid rgba(245,158,11,.3);color:#fcd34d;
}
 
/* ---------- buttons ---------- */
.buttons{display:flex;flex-direction:column;gap:.6rem;margin-top:.4rem}
.btn{
  width:100%;padding:.75rem;border:none;border-radius:8px;
  font-size:.95rem;font-weight:600;cursor:pointer;
  display:flex;align-items:center;justify-content:center;gap:.5rem;
  transition:background .2s,transform .1s,box-shadow .2s;
  letter-spacing:.01em;font-family:inherit;
}
.btn:active{transform:scale(.98)}
.btn:disabled{opacity:.7;cursor:default}
.btn-primary{background:linear-gradient(135deg,#3b82f6,#2563eb);color:#fff;box-shadow:0 4px 18px rgba(59,130,246,.35)}
.btn-primary:hover:not(:disabled){background:linear-gradient(135deg,#2563eb,#1d4ed8);box-shadow:0 6px 22px rgba(59,130,246,.45)}
.btn-ghost{background:transparent;border:1.5px solid var(--border);color:var(--sub)}
.btn-ghost:hover:not(:disabled){border-color:var(--accent);color:var(--accent)}
.spin{
  width:18px;height:18px;border:2.5px solid rgba(255,255,255,.3);
  border-top-color:#fff;border-radius:50%;animation:spin .7s linear infinite;display:none;
}
.btn.loading .spin{display:block}
.btn.loading .lbl,.btn.loading svg{display:none}
@keyframes spin{to{transform:rotate(360deg)}}
 
/* ---------- toast ---------- */
#toast{
  position:fixed;top:1.2rem;left:50%;transform:translateX(-50%) translateY(-90px);
  z-index:999;background:var(--surface);border:1px solid var(--border);
  border-radius:10px;padding:.65rem 1.2rem;font-size:.85rem;font-weight:600;
  display:flex;align-items:center;gap:.5rem;box-shadow:var(--shadow);
  transition:transform .35s cubic-bezier(.34,1.56,.64,1);pointer-events:none;
  max-width:92vw;text-align:left;
}
#toast.show{transform:translateX(-50%) translateY(0)}
#toast.success{color:var(--success);border-color:rgba(34,197,94,.3)}
#toast.error{color:var(--danger);border-color:rgba(239,68,68,.3)}
#toast.info{color:var(--accent);border-color:rgba(59,130,246,.3)}
 
/* ---------- side panels ---------- */
.status-head{display:flex;justify-content:space-between;align-items:center;margin-bottom:.8rem}
.side-title{font-size:.72rem;font-weight:700;letter-spacing:.1em;text-transform:uppercase;color:var(--accent)}
.side-right .side-title{color:var(--sub)}
.refresh-btn{background:none;border:1px solid var(--border);color:var(--sub);
  border-radius:6px;font-size:.72rem;padding:.25rem .6rem;cursor:pointer;font-family:inherit}
.refresh-btn:hover{border-color:var(--accent);color:var(--accent)}
.status-card{background:var(--surface2);border:1px solid var(--border);border-radius:8px;padding:.7rem .9rem}
.status-card + .status-card{margin-top:.7rem}
.status-sub{font-size:.68rem;font-weight:700;letter-spacing:.08em;text-transform:uppercase;color:var(--sub);margin-bottom:.3rem}
.srow{display:flex;justify-content:space-between;gap:1rem;font-size:.82rem;padding:.25rem 0}
.srow span:first-child{color:var(--sub)}
.srow span:last-child{font-weight:600;word-break:break-all;text-align:right}
.status-empty{font-size:.82rem;color:var(--sub)}
.srow-group{margin:.55rem 0 .15rem;font-size:.66rem;font-weight:700;letter-spacing:.08em;text-transform:uppercase;color:var(--accent)}
</style>
</head>
<body>
 
<div class="orb orb1"></div>
<div class="orb orb2"></div>
<div class="orb orb3"></div>
 
<div id="toast" role="status" aria-live="polite"></div>
 
<div class="layout">
 
  <!-- ================= LEFT: CURRENT ================= -->
  <div class="card side side-left">
    <div class="status-head">
      <div class="side-title">Current</div>
      <button type="button" class="refresh-btn" onclick="loadStatus()">Refresh</button>
    </div>
    <div class="status-card">
      <div id="statusCurrent" class="status-empty">Loading&#8230;</div>
    </div>
    <div class="status-card" id="liveCard" style="display:none">
      <div class="status-sub">LTE live status</div>
      <div id="statusLive"></div>
    </div>
  </div>
 
  <!-- ================= MAIN ================= -->
  <div class="card main">
 
    <div class="logo">
      <div class="logo-icon">&#x1F4E1;</div>
      <div class="logo-text">
        <h1>Sarayu Gateway</h1>
        <span>Gateway configuration portal</span>
      </div>
    </div>
 
    <div class="badge"><span class="badge-dot"></span>Setup mode active</div>
 
    <div class="tabs" role="tablist" aria-label="Configuration sections">
      <button type="button" class="tab" role="tab" id="t-net" aria-selected="true" aria-controls="p-net" onclick="showTab('net')">
        <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><path d="M5 12.55a11 11 0 0 1 14.08 0"/><path d="M1.42 9a16 16 0 0 1 21.16 0"/><path d="M8.53 16.11a6 6 0 0 1 6.95 0"/><line x1="12" y1="20" x2="12.01" y2="20"/></svg><span>Network</span>
      </button>
      <button type="button" class="tab" role="tab" id="t-srv" aria-selected="false" aria-controls="p-srv" onclick="showTab('srv')">
        <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><rect x="2" y="3" width="20" height="8" rx="2"/><rect x="2" y="13" width="20" height="8" rx="2"/><line x1="6" y1="7" x2="6.01" y2="7"/><line x1="6" y1="17" x2="6.01" y2="17"/></svg><span>Server</span>
      </button>
      <button type="button" class="tab" role="tab" id="t-loc" aria-selected="false" aria-controls="p-loc" onclick="showTab('loc')">
        <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="4 17 10 11 4 5"/><line x1="12" y1="19" x2="20" y2="19"/></svg><span>Local</span>
      </button>
      <button type="button" class="tab" role="tab" id="t-fota" aria-selected="false" aria-controls="p-fota" onclick="showTab('fota')">
        <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/><polyline points="17 8 12 3 7 8"/><line x1="12" y1="3" x2="12" y2="15"/></svg><span>FOTA</span>
      </button>
    </div>
 
    <!-- =============== NETWORK =============== -->
    <div class="panel on" id="p-net" role="tabpanel" aria-labelledby="t-net">
      <form id="networkForm" onsubmit="return false">
 
        <div class="section-label">Network mode</div>
        <div class="field">
          <label for="mode">How should this gateway connect?</label>
          <div class="input-wrap">
            <select id="mode" onchange="updateMode()">
              <option value="wifi">Wi-Fi</option>
              <option value="ethernet">Ethernet</option>
              <option value="lte">LTE (SIM)</option>
              <option value="both">Wi-Fi + Ethernet</option>
              <option value="wifi_lte">Wi-Fi + LTE</option>
              <option value="ethernet_lte">Ethernet + LTE</option>
              <option value="all">Wi-Fi + Ethernet + LTE</option>
            </select>
          </div>
        </div>
 
        <div id="wifiSection" class="section">
          <div class="divider"><span>Wi-Fi network</span></div>
          <div class="field">
            <label for="ssid">Network SSID</label>
            <div class="input-wrap"><input type="text" id="ssid" placeholder="Enter Wi-Fi SSID" autocomplete="off" maxlength="32"></div>
          </div>
          <div class="radio-group">
            <label><input type="radio" name="security" value="closed" checked onchange="updateSecurity()"> Password protected</label>
            <label><input type="radio" name="security" value="open" onchange="updateSecurity()"> Open network</label>
          </div>
          <div id="passwordSection" class="field">
            <label for="password">Password</label>
            <div class="input-wrap">
              <input type="password" id="password" placeholder="Enter password" autocomplete="off" maxlength="63">
              <button type="button" class="eye-btn" onclick="toggleEye('password','pwEye')" title="Show/hide" aria-label="Show or hide password">
                <svg id="pwEye" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>
              </button>
            </div>
            <div class="hint">Minimum 8 characters.</div>
          </div>
        </div>
 
        <div id="ethernetSection" class="section">
          <div class="divider"><span>Ethernet</span></div>
          <div class="radio-group">
            <label><input type="radio" name="ipmode" value="dhcp" checked onchange="updateIPMode()"> Dynamic IP (DHCP)</label>
            <label><input type="radio" name="ipmode" value="static" onchange="updateIPMode()"> Static IP</label>
          </div>
          <div id="staticSection">
            <div class="field"><label for="ip">IP address</label><div class="input-wrap"><input type="text" id="ip" placeholder="192.168.1.100" inputmode="decimal"></div></div>
            <div class="field"><label for="netmask">Subnet mask</label><div class="input-wrap"><input type="text" id="netmask" placeholder="255.255.255.0" inputmode="decimal"></div></div>
            <div class="field"><label for="gateway">Gateway</label><div class="input-wrap"><input type="text" id="gateway" placeholder="192.168.1.1" inputmode="decimal"></div></div>
            <div class="field"><label for="dns">DNS</label><div class="input-wrap"><input type="text" id="dns" placeholder="8.8.8.8" inputmode="decimal"></div></div>
          </div>
        </div>
 
        <div id="lteSection" class="section">
          <div class="divider"><span>LTE / SIM</span></div>
          <div class="field">
            <label for="apn">APN</label>
            <div class="input-wrap"><input type="text" id="apn" placeholder="e.g. internet" autocomplete="off" autocapitalize="off"></div>
            <div class="hint">Leave blank to use the modem or operator default, if available.</div>
          </div>
 
          <details class="adv">
            <summary>Advanced settings</summary>
            <div class="adv-body">
              <div class="field"><label for="apnUser">APN username (optional)</label><div class="input-wrap"><input type="text" id="apnUser" autocomplete="off" autocapitalize="off"></div></div>
              <div class="field">
                <label for="apnPass">APN password (optional)</label>
                <div class="input-wrap">
                  <input type="password" id="apnPass" autocomplete="off">
                  <button type="button" class="eye-btn" onclick="toggleEye('apnPass','apnEye')" title="Show/hide" aria-label="Show or hide APN password">
                    <svg id="apnEye" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>
                  </button>
                </div>
              </div>
              <div class="field">
                <label for="apnAuth">Authentication</label>
                <div class="input-wrap">
                  <select id="apnAuth">
                    <option value="auto">Automatic</option><option value="none">None</option>
                    <option value="pap">PAP</option><option value="chap">CHAP</option>
                  </select>
                </div>
              </div>
              <div class="field">
                <label for="simPin">SIM PIN (only if enabled)</label>
                <div class="input-wrap">
                  <input type="password" id="simPin" inputmode="numeric" maxlength="8" autocomplete="off">
                  <button type="button" class="eye-btn" onclick="toggleEye('simPin','pinEye')" title="Show/hide" aria-label="Show or hide SIM PIN">
                    <svg id="pinEye" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>
                  </button>
                </div>
                <div class="hint">4 to 8 digits.</div>
              </div>
              <div class="field">
                <label for="netPref">Network preference</label>
                <div class="input-wrap">
                  <select id="netPref">
                    <option value="auto">Automatic (recommended)</option>
                    <option value="lte_only">4G / LTE only</option>
                  </select>
                </div>
              </div>
              <div class="field">
                <label for="lteIpMode">IP assignment</label>
                <div class="input-wrap"><select id="lteIpMode" disabled><option value="dynamic">Dynamic IP (automatic)</option></select></div>
                <div class="hint">The mobile network assigns the IP address. A static or private IP depends on your operator and SIM plan.</div>
              </div>
            </div>
          </details>
        </div>
 
        <div id="prioritySection" class="section">
          <div class="divider"><span>Network priority</span></div>
          <div class="field">
            <label id="priorityLabel" for="priority">Which connection should this gateway prefer?</label>
            <div class="input-wrap"><select id="priority"></select></div>
            <div class="hint">The first connection is preferred. If it does not connect within 20 seconds, the gateway falls back to the next one.</div>
          </div>
        </div>
 
        <div class="buttons">
          <button type="button" class="btn btn-primary" id="saveBtn" onclick="saveConfiguration()">
            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><path d="M5 12.55a11 11 0 0 1 14.08 0"/><path d="M1.42 9a16 16 0 0 1 21.16 0"/><path d="M8.53 16.11a6 6 0 0 1 6.95 0"/><line x1="12" y1="20" x2="12.01" y2="20"/></svg>
            <span class="lbl">Save &amp; Connect</span><div class="spin"></div>
          </button>
        </div>
      </form>
    </div>
 
    <!-- =============== SERVER =============== -->
    <div class="panel" id="p-srv" role="tabpanel" aria-labelledby="t-srv">
      <form onsubmit="return false">
        <div class="section-label">MQTT broker</div>
        <div class="field">
          <label for="mqttHost">MQTT IP / host</label>
          <div class="input-wrap"><input type="text" id="mqttHost" placeholder="192.168.1.50 or broker.example.com" autocomplete="off" autocapitalize="off" maxlength="253"></div>
        </div>
 
        <div class="field">
          <span class="lab">Connection security</span>
          <div class="opt-grid" role="radiogroup" aria-label="Connection security">
            <label class="opt"><input type="radio" name="srvMode" value="plain" checked onchange="updateServerMode()"><b>Unencrypted</b><small>Port 1883</small></label>
            <label class="opt"><input type="radio" name="srvMode" value="auth" onchange="updateServerMode()"><b>Authentication</b><small>Port 1883 + user / pass</small></label>
            <label class="opt"><input type="radio" name="srvMode" value="tls" onchange="updateServerMode()"><b>TLS / SSL</b><small>Port 8883</small></label>
            <label class="opt"><input type="radio" name="srvMode" value="tlsauth" onchange="updateServerMode()"><b>Authenticated TLS / SSL</b><small>Port 8883 + user / pass</small></label>
          </div>
        </div>
 
        <div class="field">
          <label for="mqttPort">Port</label>
          <div class="input-wrap"><input type="text" id="mqttPort" value="1883" readonly></div>
        </div>
 
        <div id="srvAuth" class="section">
          <div class="divider"><span>Credentials</span></div>
          <div class="field"><label for="mqttUser">Username</label><div class="input-wrap"><input type="text" id="mqttUser" autocomplete="off" autocapitalize="off" maxlength="64"></div></div>
          <div class="field">
            <label for="mqttPass">Password</label>
            <div class="input-wrap">
              <input type="password" id="mqttPass" autocomplete="off" maxlength="64">
              <button type="button" class="eye-btn" onclick="toggleEye('mqttPass','mqEye')" title="Show/hide" aria-label="Show or hide MQTT password">
                <svg id="mqEye" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>
              </button>
            </div>
          </div>
        </div>
 
        <div id="srvTls" class="section">
          <div class="divider"><span>TLS certificates</span></div>
          <div class="field"><span class="lab">CA certificate</span><div id="dz_ca"></div></div>
          <div class="field"><span class="lab">Client certificate</span><div id="dz_crt"></div></div>
          <div class="field">
            <span class="lab">Client private key</span><div id="dz_key"></div>
            <div class="hint">PEM text files only, 16 KB maximum each. Binary (DER) files and password-protected keys are rejected.</div>
          </div>
        </div>
 
        <div class="buttons">
          <button type="button" class="btn btn-primary" id="srvBtn" onclick="saveServer()">
            <span class="lbl">Save server settings</span><div class="spin"></div>
          </button>
        </div>
      </form>
    </div>
 
    <!-- =============== LOCAL =============== -->
    <div class="panel" id="p-loc" role="tabpanel" aria-labelledby="t-loc">
      <form onsubmit="return false">
        <div class="section-label">Modbus RTU</div>
        <div class="switch-row">
          <div><b>Enable Modbus RTU</b><small>Serial (RS-485) interface</small></div>
          <label class="switch"><input type="checkbox" id="rtuOn" checked aria-label="Enable Modbus RTU"><i></i></label>
        </div>
 
        <div class="divider"><span>Modbus TCP/IP</span></div>
        <div class="switch-row">
          <div><b>Enable Modbus TCP/IP</b><small>Over the Ethernet port</small></div>
          <label class="switch"><input type="checkbox" id="tcpOn" checked onchange="updateLocal()" aria-label="Enable Modbus TCP/IP"><i></i></label>
        </div>
 
        <div id="tcpBody">
          <div class="radio-group">
            <label><input type="radio" name="tcpip" value="dhcp" checked onchange="updateLocal()"> DHCP</label>
            <label><input type="radio" name="tcpip" value="static" onchange="updateLocal()"> Static IP</label>
          </div>
          <div id="tcpStatic" class="section">
            <div class="field"><label for="tcpIp">IP address</label><div class="input-wrap"><input type="text" id="tcpIp" placeholder="192.168.1.120" inputmode="decimal"></div></div>
            <div class="field"><label for="tcpMask">Subnet mask</label><div class="input-wrap"><input type="text" id="tcpMask" placeholder="255.255.255.0" inputmode="decimal"></div></div>
            <div class="field"><label for="tcpGw">Gateway</label><div class="input-wrap"><input type="text" id="tcpGw" placeholder="192.168.1.1" inputmode="decimal"></div></div>
          </div>
        </div>
 
        <div class="buttons">
          <button type="button" class="btn btn-primary" id="locBtn" onclick="saveLocal()">
            <span class="lbl">Save local settings</span><div class="spin"></div>
          </button>
        </div>
      </form>
    </div>
 
    <!-- =============== FOTA =============== -->
    <div class="panel" id="p-fota" role="tabpanel" aria-labelledby="t-fota">
      <form onsubmit="return false">
        <div class="section-label">Firmware update</div>
        <div class="notice">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round" style="flex:none;margin-top:1px"><path d="M10.29 3.86L1.82 18a2 2 0 0 0 1.71 3h16.94a2 2 0 0 0 1.71-3L13.71 3.86a2 2 0 0 0-3.42 0z"/><line x1="12" y1="9" x2="12" y2="13"/><line x1="12" y1="17" x2="12.01" y2="17"/></svg>
          <span>Do not power off the gateway or close this page during the update. The gateway restarts when it finishes.</span>
        </div>
 
        <div class="field">
          <label for="fotaPass">Password</label>
          <div class="input-wrap">
            <input type="password" id="fotaPass" autocomplete="off" maxlength="64" placeholder="Enter FOTA password">
            <button type="button" class="eye-btn" onclick="toggleEye('fotaPass','fotaEye')" title="Show/hide" aria-label="Show or hide FOTA password">
              <svg id="fotaEye" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/></svg>
            </button>
          </div>
        </div>
 
        <div class="field"><span class="lab">Firmware file</span><div id="dz_fw"></div></div>
 
        <div class="field">
          <div class="progress" role="progressbar" aria-valuemin="0" aria-valuemax="100" aria-valuenow="0" id="fwProg"><div id="fwBar"></div></div>
          <div class="progress-meta"><span id="fwState">Idle</span><span id="fwPct">0%</span></div>
        </div>
 
        <div class="buttons">
          <button type="button" class="btn btn-primary" id="fwBtn" onclick="startFota()">
            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/><polyline points="17 8 12 3 7 8"/><line x1="12" y1="3" x2="12" y2="15"/></svg>
            <span class="lbl">Upload &amp; update</span><div class="spin"></div>
          </button>
        </div>
      </form>
    </div>
 
    <div class="divider"><span>Session</span></div>
    <div class="buttons" style="margin-top:0">
      <button type="button" class="btn btn-ghost" id="cancelBtn" onclick="cancelConfiguration()">
        <span class="lbl">Exit AP mode</span><div class="spin"></div>
      </button>
    </div>
 
  </div>
 
  <!-- ================= RIGHT: PREVIOUS ================= -->
  <div class="card side side-right">
    <div class="status-head"><div class="side-title">Previous</div></div>
    <div class="status-card">
      <div id="statusPrevious" class="status-empty">Loading&#8230;</div>
    </div>
  </div>
 
</div>
 
<script>
function $(id){return document.getElementById(id)}
 
/* ---------------- constants ---------------- */
var MAX_CERT = 16384;     // bytes per certificate / key
var MAX_FW   = 1966080;   // bytes; keep at or below the OTA partition size
var FW_MAGIC = 0xE9;      // first byte of an ESP32 application image
 
var MODE_LABELS={
  wifi:'Wi-Fi', ethernet:'Ethernet', lte:'LTE',
  both:'Wi-Fi + Ethernet', wifi_lte:'Wi-Fi + LTE',
  ethernet_lte:'Ethernet + LTE', all:'Wi-Fi + Ethernet + LTE'
};
var SRV_LABELS={
  plain:'Unencrypted', auth:'Authentication',
  tls:'TLS / SSL', tlsauth:'Authenticated TLS / SSL'
};
 
var PRIORITY_OPTIONS={
  both:[['wifi_first','Wi-Fi \u2192 Ethernet'],['ethernet_first','Ethernet \u2192 Wi-Fi']],
  wifi_lte:[['wifi_first','Wi-Fi \u2192 LTE'],['lte_first','LTE \u2192 Wi-Fi']],
  ethernet_lte:[['ethernet_first','Ethernet \u2192 LTE'],['lte_first','LTE \u2192 Ethernet']],
  all:[
    ['wifi_ethernet_lte','Wi-Fi \u2192 Ethernet \u2192 LTE'],
    ['wifi_lte_ethernet','Wi-Fi \u2192 LTE \u2192 Ethernet'],
    ['ethernet_wifi_lte','Ethernet \u2192 Wi-Fi \u2192 LTE'],
    ['ethernet_lte_wifi','Ethernet \u2192 LTE \u2192 Wi-Fi'],
    ['lte_wifi_ethernet','LTE \u2192 Wi-Fi \u2192 Ethernet'],
    ['lte_ethernet_wifi','LTE \u2192 Ethernet \u2192 Wi-Fi']
  ]
};
 
function priorityLabel(mode,val){
  var list=PRIORITY_OPTIONS[mode]||[];
  for(var i=0;i<list.length;i++){ if(list[i][0]===val) return list[i][1]; }
  return val;
}
function parts(m){
  return {
    wifi:['wifi','both','wifi_lte','all'].indexOf(m)>-1,
    eth:['ethernet','both','ethernet_lte','all'].indexOf(m)>-1,
    lte:['lte','wifi_lte','ethernet_lte','all'].indexOf(m)>-1,
    multi:!!PRIORITY_OPTIONS[m]
  };
}
 
/* ---------------- ui helpers ---------------- */
var TABS=['net','srv','loc','fota'];
function showTab(id){
  TABS.forEach(function(k){
    var on=(k===id);
    $('p-'+k).className='panel'+(on?' on':'');
    $('t-'+k).setAttribute('aria-selected',on?'true':'false');
  });
}
 
function toast(msg,type,dur){
  var t=$('toast');
  t.className='';t.innerHTML=msg;
  void t.offsetWidth;
  t.className=type+' show';
  clearTimeout(t._t);
  t._t=setTimeout(function(){t.className=type},dur||3500);
}
 
function toggleEye(inputId,svgId){
  var inp=$(inputId),svg=$(svgId);
  if(inp.type==='password'){
    inp.type='text';
    svg.innerHTML='<path d="M17.94 17.94A10.07 10.07 0 0 1 12 20c-7 0-11-8-11-8a18.45 18.45 0 0 1 5.06-5.94"/><path d="M9.9 4.24A9.12 9.12 0 0 1 12 4c7 0 11 8 11 8a18.5 18.5 0 0 1-2.16 3.19"/><line x1="1" y1="1" x2="23" y2="23"/>';
  }else{
    inp.type='password';
    svg.innerHTML='<path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"/><circle cx="12" cy="12" r="3"/>';
  }
}
 
function busy(btnId,state){
  var b=$(btnId);
  b.disabled=state;
  if(state) b.classList.add('loading'); else b.classList.remove('loading');
}
 
function mark(ids,bad){
  ids.forEach(function(i){ var e=$(i); if(e) e.classList[bad?'add':'remove']('invalid'); });
}
function clearInvalid(){
  var all=document.querySelectorAll('.invalid');
  for(var i=0;i<all.length;i++) all[i].classList.remove('invalid');
}
function fail(id,text){
  var e=$(id);
  if(e){ e.classList.add('invalid'); try{e.focus()}catch(x){} }
  toast('&#x26A0; '+text,'error',4500);
}
 
/* ---------------- validators ---------------- */
function isIPv4(s){
  var m=/^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$/.exec(s);
  if(!m) return false;
  for(var i=1;i<=4;i++){ if(parseInt(m[i],10)>255) return false; }
  return true;
}
function isMask(s){
  if(!isIPv4(s)) return false;
  var n=s.split('.').reduce(function(a,o){return (a*256)+parseInt(o,10)},0);
  if(n===0) return false;
  var inv=(~n)>>>0;
  return ((inv+1)&inv)===0;
}
function isHost(s){
  if(isIPv4(s)) return true;
  if(/^[\d.]+$/.test(s)) return false;
  return /^(?=.{1,253}$)([a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)(\.[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/.test(s);
}
function extOf(name){ var i=name.lastIndexOf('.'); return i<0 ? '' : name.slice(i).toLowerCase(); }
function fmtBytes(n){ return n.toLocaleString('en-US')+' bytes'; }
function selVal(name){ return document.querySelector('input[name="'+name+'"]:checked').value; }
 
/* ---------------- network tab ---------------- */
function fillPriority(mode){
  var sel=$("priority"), prev=sel.value, list=PRIORITY_OPTIONS[mode]||[];
  sel.innerHTML='';
  list.forEach(function(o){
    var op=document.createElement('option');
    op.value=o[0]; op.textContent=o[1]; sel.appendChild(op);
  });
  for(var i=0;i<list.length;i++){ if(list[i][0]===prev){ sel.value=prev; break; } }
  $("priorityLabel").textContent=(mode==='all')
    ? 'Connection order (first is preferred, the rest are fallbacks)'
    : 'Which connection should this gateway prefer?';
}
function updateMode(){
  var mode=$("mode").value, p=parts(mode);
  $("wifiSection").style.display=p.wifi?"block":"none";
  $("ethernetSection").style.display=p.eth?"block":"none";
  $("lteSection").style.display=p.lte?"block":"none";
  $("prioritySection").style.display=p.multi?"block":"none";
  if(p.multi) fillPriority(mode);
}
function updateSecurity(){
  $("passwordSection").style.display = selVal('security')==="closed" ? "block" : "none";
}
function updateIPMode(){
  $("staticSection").style.display = selVal('ipmode')==="static" ? "block" : "none";
}
 
function saveConfiguration(){
  clearInvalid();
  var mode=$("mode").value, p=parts(mode);
  var ssid=$("ssid").value.trim(), security=selVal('security'), password=$("password").value;
  var ipmode=selVal('ipmode');
  var ip=$("ip").value.trim(), netmask=$("netmask").value.trim();
  var gateway=$("gateway").value.trim(), dns=$("dns").value.trim();
  var apn=$("apn").value.trim(), apnUser=$("apnUser").value.trim();
  var apnPass=$("apnPass").value, apnAuth=$("apnAuth").value;
  var simPin=$("simPin").value.trim(), netPref=$("netPref").value;
  var priority=p.multi ? $("priority").value : "";
 
  if(p.wifi){
    if(!ssid) return fail('ssid',"Please enter the Wi-Fi SSID");
    if(security==="closed" && password.length<8) return fail('password',"Wi-Fi password must contain at least 8 characters");
  }
  if(p.eth && ipmode==="static"){
    if(!isIPv4(ip))      return fail('ip',"Ethernet IP address is not a valid IPv4 address");
    if(!isMask(netmask)) return fail('netmask',"Ethernet subnet mask is not valid, for example 255.255.255.0");
    if(!isIPv4(gateway)) return fail('gateway',"Ethernet gateway is not a valid IPv4 address");
    if(!isIPv4(dns))     return fail('dns',"Ethernet DNS is not a valid IPv4 address");
  }
  if(p.lte){
    if((apnAuth==="pap"||apnAuth==="chap") && !apnUser){
      $('p-net').querySelector('details.adv').open=true;
      return fail('apnUser',"APN username is required for PAP / CHAP");
    }
    if(simPin && !/^\d{4,8}$/.test(simPin)){
      $('p-net').querySelector('details.adv').open=true;
      return fail('simPin',"SIM PIN must be 4 to 8 digits");
    }
  }
 
  var config={
    mode:mode, priority:priority, timeout:20,
    wifi:{ ssid:ssid, security:security, password:password },
    ethernet:{ ip_mode:ipmode, ip:ip, netmask:netmask, gateway:gateway, dns:dns },
    lte:{ apn:apn, username:apnUser, password:apnPass, auth:apnAuth,
          pin:simPin, network_pref:netPref, ip_mode:"dynamic", timeout:20 }
  };
 
  busy('saveBtn',true);
  toast("Saving and exiting AP mode&#8230;","info",4000);
  fetch("/save",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify(config)})
  .then(function(r){return r.json()})
  .then(function(d){
    busy('saveBtn',false);
    if(d.success) toast("&#x2705; Configuration saved - connecting with new credentials&#8230;","success",5000);
    else toast("&#x274C; "+d.message,"error",5000);
  })
  .catch(function(e){
    console.error(e);
    busy('saveBtn',false);
    toast("Exiting AP mode - connecting with new network settings","info",5000);
  });
}
 
/* ---------------- drop zones ---------------- */
var ICON_UP='<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/><polyline points="17 8 12 3 7 8"/><line x1="12" y1="3" x2="12" y2="15"/></svg>';
var ICON_OK='<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.6" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"/></svg>';
var ICON_ERR='<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><line x1="12" y1="8" x2="12" y2="12"/><line x1="12" y1="16" x2="12.01" y2="16"/></svg>';
 
/* slot -> {title, accept hint, extensions, handler} */
var DZ={};
function buildDrop(slot,title,hint,accept,onFile,onClear){
  var host=$('dz_'+slot);
  host.innerHTML=
    '<div class="dz" id="zone_'+slot+'" role="button" tabindex="0" aria-label="'+title+'">'+
      '<div class="dz-ico" id="ico_'+slot+'">'+ICON_UP+'</div>'+
      '<div class="dz-txt"><div class="dz-title" id="ttl_'+slot+'">'+title+'</div>'+
      '<div class="dz-sub" id="sub_'+slot+'">'+hint+'</div></div>'+
      '<button type="button" class="dz-clear" id="clr_'+slot+'" aria-label="Remove file">&times;</button>'+
      '<input type="file" id="in_'+slot+'" accept="'+accept+'">'+
    '</div>';
  var z=$('zone_'+slot), inp=$('in_'+slot);
  DZ[slot]={title:title,hint:hint,onClear:onClear};
  z.addEventListener('click',function(e){ if(e.target.closest('.dz-clear')) return; inp.click(); });
  z.addEventListener('keydown',function(e){ if(e.key==='Enter'||e.key===' '){ e.preventDefault(); inp.click(); } });
  inp.addEventListener('change',function(){ if(inp.files[0]) onFile(inp.files[0]); });
  ['dragenter','dragover'].forEach(function(ev){
    z.addEventListener(ev,function(e){ e.preventDefault(); z.classList.add('drag'); });
  });
  ['dragleave','drop'].forEach(function(ev){
    z.addEventListener(ev,function(e){ e.preventDefault(); z.classList.remove('drag'); });
  });
  z.addEventListener('drop',function(e){
    var f=e.dataTransfer && e.dataTransfer.files[0];
    if(f) onFile(f);
  });
  $('clr_'+slot).addEventListener('click',function(e){ e.stopPropagation(); resetDrop(slot); });
}
function dzState(slot,state,title,sub){
  var z=$('zone_'+slot);
  z.className='dz'+(state?' '+state:'');
  $('ico_'+slot).innerHTML = state==='ok' ? ICON_OK : state==='err' ? ICON_ERR : ICON_UP;
  $('ttl_'+slot).textContent=title;
  $('sub_'+slot).textContent=sub;
}
function resetDrop(slot){
  $('in_'+slot).value='';
  dzState(slot,'',DZ[slot].title,DZ[slot].hint);
  if(DZ[slot].onClear) DZ[slot].onClear();
}
function dzReject(slot,fileName,reason){
  $('in_'+slot).value='';
  dzState(slot,'err',fileName||DZ[slot].title,reason);
  if(DZ[slot].onClear) DZ[slot].onClear();
  toast('&#x26A0; '+DZ[slot].title+': '+reason,'error',5000);
}
 
/* ---------------- server tab ---------------- */
var certs={ca:null,crt:null,key:null};
var CERT_SPEC={
  ca:{  label:'CA certificate',     ext:['.ca','.crt','.pem'], kind:'cert', hint:'Upload .ca / .crt / .pem' },
  crt:{ label:'Client certificate', ext:['.crt','.pem'],       kind:'cert', hint:'Upload .crt / .pem' },
  key:{ label:'Client private key', ext:['.key','.pem'],       kind:'key',  hint:'Upload .key / .pem' }
};
 
function checkPem(kind,text){
  if(/[\u0000-\u0008\u000e-\u001f]/.test(text)) return 'Binary (DER) file. A PEM text file is required.';
  if(kind==='cert'){
    if(text.indexOf('-----BEGIN CERTIFICATE-----')<0 || text.indexOf('-----END CERTIFICATE-----')<0)
      return 'Not a PEM certificate (BEGIN / END CERTIFICATE not found).';
    return '';
  }
  if(/-----BEGIN ENCRYPTED PRIVATE KEY-----/.test(text) || /Proc-Type:\s*4,ENCRYPTED/.test(text))
    return 'Key is password-protected. Use an unencrypted key.';
  if(!/-----BEGIN (RSA |EC )?PRIVATE KEY-----/.test(text) || !/-----END (RSA |EC )?PRIVATE KEY-----/.test(text))
    return 'Not a PEM private key (BEGIN / END PRIVATE KEY not found).';
  return '';
}
 
function handleCert(slot,f){
  var spec=CERT_SPEC[slot];
  certs[slot]=null;
  var ext=extOf(f.name);
  if(spec.ext.indexOf(ext)<0) return dzReject(slot,f.name,'"'+(ext||'no extension')+'" is not allowed. Use '+spec.ext.join(' / ')+'.');
  if(f.size===0)              return dzReject(slot,f.name,'File is empty.');
  if(f.size>MAX_CERT)         return dzReject(slot,f.name,'File is larger than '+(MAX_CERT/1024)+' KB.');
  var r=new FileReader();
  r.onerror=function(){ dzReject(slot,f.name,'Could not read the file.'); };
  r.onload=function(){
    var text=String(r.result).replace(/\r\n?/g,'\n').trim();
    var err=checkPem(spec.kind,text);
    if(err) return dzReject(slot,f.name,err);
    certs[slot]=text+'\n';
    dzState(slot,'ok',f.name,fmtBytes(f.size)+' \u00B7 valid PEM');
  };
  r.readAsText(f);
}
 
function updateServerMode(){
  var m=selVal('srvMode');
  var auth=(m==='auth'||m==='tlsauth'), tls=(m==='tls'||m==='tlsauth');
  $("srvAuth").style.display=auth?"block":"none";
  $("srvTls").style.display=tls?"block":"none";
  $("mqttPort").value=tls?"8883":"1883";
}
 
function saveServer(){
  clearInvalid();
  var m=selVal('srvMode');
  var auth=(m==='auth'||m==='tlsauth'), tls=(m==='tls'||m==='tlsauth');
  var host=$("mqttHost").value.trim();
  var user=$("mqttUser").value.trim(), pass=$("mqttPass").value;
 
  if(!host)        return fail('mqttHost',"Please enter the MQTT IP address or host name");
  if(!isHost(host))return fail('mqttHost',"MQTT address is not a valid IPv4 address or host name");
  if(auth){
    if(!user) return fail('mqttUser',"Please enter the MQTT username");
    if(!pass) return fail('mqttPass',"Please enter the MQTT password");
  }
  if(tls){
    var miss=[['ca','CA certificate'],['crt','client certificate'],['key','client private key']];
    for(var i=0;i<miss.length;i++){
      if(!certs[miss[i][0]]){
        $('zone_'+miss[i][0]).classList.add('err');
        $('zone_'+miss[i][0]).focus();
        toast('&#x26A0; Upload a valid '+miss[i][1],'error',4500);
        return;
      }
    }
  }
  var cfg={ mqtt:{
    host:host, mode:m, port:parseInt($("mqttPort").value,10),
    username:auth?user:"", password:auth?pass:"",
    ca:tls?certs.ca:"", client_cert:tls?certs.crt:"", client_key:tls?certs.key:""
  }};
  postJson('/save_server',cfg,'srvBtn','Server settings saved');
}
 
/* ---------------- local tab ---------------- */
function updateLocal(){
  var on=$("tcpOn").checked, st=selVal('tcpip')==='static';
  $("tcpBody").style.opacity=on?'1':'.45';
  var radios=document.getElementsByName('tcpip');
  for(var i=0;i<radios.length;i++) radios[i].disabled=!on;
  $("tcpStatic").style.display=(on&&st)?"block":"none";
}
 
function saveLocal(){
  clearInvalid();
  var tcp=$("tcpOn").checked, mode=selVal('tcpip');
  var ip=$("tcpIp").value.trim(), mask=$("tcpMask").value.trim(), gw=$("tcpGw").value.trim();
  if(tcp && mode==='static'){
    if(!isIPv4(ip))   return fail('tcpIp',"Modbus TCP IP address is not a valid IPv4 address");
    if(!isMask(mask)) return fail('tcpMask',"Modbus TCP subnet mask is not valid, for example 255.255.255.0");
    if(!isIPv4(gw))   return fail('tcpGw',"Modbus TCP gateway is not a valid IPv4 address");
  }
  var cfg={
    modbus_rtu:{ enabled:$("rtuOn").checked },
    modbus_tcp:{ enabled:tcp, ip_mode:mode, ip:ip, netmask:mask, gateway:gw }
  };
  postJson('/save_local',cfg,'locBtn','Local settings saved');
}
 
/* ---------------- fota tab ---------------- */
var fwFile=null;
 
function handleFirmware(f){
  fwFile=null; setProgress(0,'Idle');
  if(extOf(f.name)!=='.bin') return dzReject('fw',f.name,'Only .bin files are allowed.');
  if(f.size===0)             return dzReject('fw',f.name,'File is empty.');
  if(f.size>MAX_FW)          return dzReject('fw',f.name,'File is larger than the update partition ('+fmtBytes(MAX_FW)+').');
  var r=new FileReader();
  r.onerror=function(){ dzReject('fw',f.name,'Could not read the file.'); };
  r.onload=function(){
    var b=new Uint8Array(r.result);
    if(b[0]!==FW_MAGIC) return dzReject('fw',f.name,'Header check failed. This is not a valid firmware image.');
    fwFile=f;
    dzState('fw','ok',f.name,fmtBytes(f.size)+' \u00B7 header ok');
  };
  r.readAsArrayBuffer(f.slice(0,4));
}
 
function setProgress(pct,state){
  $('fwBar').style.width=pct+'%';
  $('fwPct').textContent=pct+'%';
  $('fwState').textContent=state;
  $('fwProg').setAttribute('aria-valuenow',pct);
}
 
function startFota(){
  clearInvalid();
  var pass=$('fotaPass').value;
  if(!pass) return fail('fotaPass',"Please enter the FOTA password");
  if(!fwFile){
    $('zone_fw').classList.add('err'); $('zone_fw').focus();
    toast("&#x26A0; Choose a valid .bin firmware file first","error",4500);
    return;
  }
  if(!confirm("Start firmware update with "+fwFile.name+"?\nThe gateway will restart afterwards.")) return;
 
  var fd=new FormData();
  fd.append('password',pass);
  fd.append('firmware',fwFile,fwFile.name);
 
  var xhr=new XMLHttpRequest();
  xhr.open('POST','/fota');
  busy('fwBtn',true);
  setProgress(0,'Uploading');
 
  xhr.upload.onprogress=function(e){
    if(!e.lengthComputable) return;
    setProgress(Math.round(e.loaded*100/e.total),'Uploading');
  };
  xhr.onload=function(){
    busy('fwBtn',false);
    var d=null; try{ d=JSON.parse(xhr.responseText); }catch(x){}
    if(xhr.status>=200 && xhr.status<300 && (!d || d.success!==false)){
      setProgress(100,'Complete - gateway restarting');
      toast("&#x2705; Firmware uploaded - gateway is restarting&#8230;","success",6000);
    }else{
      setProgress(0,'Failed');
      toast("&#x274C; Update failed: "+((d&&d.message)||('HTTP '+xhr.status)),"error",6000);
    }
  };
  xhr.onerror=function(){
    busy('fwBtn',false);
    setProgress(0,'Connection lost');
    toast("&#x274C; Connection lost during upload. Wait for the gateway to restart, then check the version.","error",7000);
  };
  xhr.send(fd);
}
 
/* ---------------- generic post / cancel ---------------- */
function postJson(url,body,btn,okText){
  busy(btn,true);
  fetch(url,{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify(body)})
  .then(function(r){return r.json()})
  .then(function(d){
    busy(btn,false);
    if(d.success) toast("&#x2705; "+okText,"success",4000);
    else toast("&#x274C; "+d.message,"error",5000);
  })
  .catch(function(e){
    console.error(e);
    busy(btn,false);
    toast("&#x274C; Could not reach the gateway. Settings were not saved.","error",5000);
  });
}
 
function cancelConfiguration(){
  if(!confirm("Exit AP mode and return to normal operation?")) return;
  busy('cancelBtn',true);
  toast("Exiting AP mode and reconnecting to network&#8230;","info",4000);
  fetch("/cancel",{method:"POST"})
  .then(function(r){return r.json()})
  .then(function(d){
    busy('cancelBtn',false);
    if(d.success) toast("&#x2705; Exiting AP mode - device will reconnect to saved network","success",5000);
    else toast("&#x274C; "+d.message,"error",5000);
  })
  .catch(function(e){
    console.error(e);
    busy('cancelBtn',false);
    toast("Exiting AP mode - device reconnecting","info",4000);
  });
}
 
/* ---------------- status panels ---------------- */
function addRows(box,rows){
  rows.forEach(function(r){
    if(r.group){
      var g=document.createElement('div'); g.className='srow-group'; g.textContent=r.group;
      box.appendChild(g); return;
    }
    var d=document.createElement('div'); d.className='srow';
    var a=document.createElement('span'); a.textContent=r[0];
    var b=document.createElement('span');
    b.textContent=(r[1]===undefined||r[1]===null||r[1]==='') ? '-' : r[1];
    d.appendChild(a); d.appendChild(b); box.appendChild(d);
  });
}
 
function renderStatus(id,cfg){
  var box=$(id); box.innerHTML='';
  if(!cfg){ box.className='status-empty'; box.textContent='Not available'; return; }
  if(cfg.error){ box.className='status-empty'; box.textContent='Error: '+cfg.error; return; }
  box.className='';
 
  var p=parts(cfg.mode);
  var rows=[['Mode',MODE_LABELS[cfg.mode]||cfg.mode]];
  var wifi=cfg.wifi||{}, eth=cfg.ethernet||{}, lte=cfg.lte||{};
 
  if(p.multi) rows.push(['Priority',priorityLabel(cfg.mode,cfg.priority)]);
  if(p.wifi){
    rows.push(['Wi-Fi SSID',wifi.ssid||'-']);
    rows.push(['Security',wifi.security]);
    if(wifi.security==='closed') rows.push(['Password',wifi.password||'-']);
  }
  if(p.eth){
    rows.push(['IP mode',eth.ip_mode]);
    if(eth.ip_mode==='static'){
      rows.push(['IP',eth.ip],['Netmask',eth.netmask],['Gateway',eth.gateway],['DNS',eth.dns]);
    }
  }
  if(p.lte){
    rows.push(['APN',lte.apn||'Auto']);
    if(lte.username) rows.push(['APN user',lte.username]);
    if(lte.password) rows.push(['APN password','\u2022\u2022\u2022\u2022\u2022\u2022']);
    rows.push(['APN auth',lte.auth||'auto']);
    if(lte.pin) rows.push(['SIM PIN','\u2022\u2022\u2022\u2022']);
    rows.push(['Network pref',lte.network_pref==='lte_only' ? '4G / LTE only' : 'Automatic']);
  }
 
  /* optional: server / local blocks, shown only if the firmware reports them */
  if(cfg.mqtt){
    rows.push({group:'Server'});
    rows.push(['Broker',cfg.mqtt.host]);
    rows.push(['Security',SRV_LABELS[cfg.mqtt.mode]||cfg.mqtt.mode]);
    rows.push(['Port',cfg.mqtt.port]);
    if(cfg.mqtt.username) rows.push(['Username',cfg.mqtt.username]);
  }
  if(cfg.modbus_rtu || cfg.modbus_tcp){
    rows.push({group:'Local'});
    if(cfg.modbus_rtu) rows.push(['Modbus RTU',cfg.modbus_rtu.enabled?'Enabled':'Disabled']);
    if(cfg.modbus_tcp){
      rows.push(['Modbus TCP',cfg.modbus_tcp.enabled?'Enabled':'Disabled']);
      if(cfg.modbus_tcp.enabled){
        rows.push(['TCP IP mode',cfg.modbus_tcp.ip_mode]);
        if(cfg.modbus_tcp.ip_mode==='static') rows.push(['TCP IP',cfg.modbus_tcp.ip]);
      }
    }
  }
  addRows(box,rows);
}
 
function renderLive(live){
  var card=$('liveCard'), box=$('statusLive');
  box.innerHTML='';
  if(!live){ card.style.display='none'; return; }
  card.style.display='block';
  addRows(box,[
    ['SIM',live.sim],['Operator',live.operator],['Signal',live.signal],
    ['Registration',live.registration],['Connection',live.connection]
  ]);
}
 
function loadStatus(){
  fetch('/status')
  .then(function(r){return r.json()})
  .then(function(d){
    renderStatus('statusCurrent',d.current);
    renderStatus('statusPrevious',d.previous);
    renderLive(d.lte_live);
  })
  .catch(function(){
    $('statusCurrent').textContent='Could not load status';
    $('statusPrevious').textContent='Could not load status';
  });
}
 
/* ---------------- init ---------------- */
['ca','crt','key'].forEach(function(slot){
  var s=CERT_SPEC[slot];
  buildDrop(slot,s.label,s.hint+' (click or drop)',s.ext.join(','),
    function(f){ handleCert(slot,f); },
    function(){ certs[slot]=null; });
});
buildDrop('fw','Firmware image','Upload file (.bin) (click or drop)','.bin',handleFirmware,
  function(){ fwFile=null; setProgress(0,'Idle'); });
 
updateMode();
updateSecurity();
updateIPMode();
updateServerMode();
updateLocal();
loadStatus();
</script>
</body>
</html>
)rawliteral";
 

// Send HTML from Flash memory
void handleRoot() {
  server.send_P(200, "text/html", GATEWAY_HTML);
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
    
    Serial.println("\n📌 Save & Connect button pressed - saving new configuration");
    
    // Send response first
    server.send(200, "application/json", "{\"success\":true,\"message\":\"Configuration saved, connecting with new credentials\"}");
    
    // Small delay to ensure response is sent
    delay(100);
    
    // Exit AP mode and connect with NEW credentials
    exitAPMode();
  } else {
    server.send(400, "application/json", "{\"success\":false,\"message\":\"No data received\"}");
  }
}

void handleCancel() {
  Serial.println("\n📌 Cancel button pressed - exiting AP mode");
  
  // Send response first
  server.send(200, "application/json", "{\"success\":true,\"message\":\"Exiting AP mode and reconnecting\"}");
  
  // Small delay to ensure response is sent
  delay(100);
  
  // Exit AP mode and reconnect
  exitAPMode();
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
