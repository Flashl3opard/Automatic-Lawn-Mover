"use client";
import { useState } from "react";
import axios from "axios";

export default function Home() {
  const [ip, setIp] = useState("192.168.4.1");
  const [status, setStatus] = useState("");
  const [pairing, setPairing] = useState(false);
  const [paired, setPaired] = useState(false);
  const [bladeOn, setBladeOn] = useState(false);

  // Pairing handler
  const handlePair = async () => {
    setPairing(true);
    setStatus("Pairing...");
    try {
      await axios.get(`http://${ip}/`);
      setPaired(true);
      setStatus("✅ Paired Successfully");
    } catch {
      setStatus("❌ Pairing failed: NodeMCU not found");
      setPaired(false);
    }
    setPairing(false);
  };

  // Send command helper
  const sendCommand = async (cmd: string) => {
    if (!paired) {
      setStatus("⚠️ Please pair first");
      return;
    }
    try {
      await axios.get(`http://${ip}/?State=${cmd}`);
      setStatus(`✅ Command Sent: ${cmd}`);
    } catch {
      setStatus(`❌ Failed to send: ${cmd}`);
    }
  };

  // Blade toggle with command send
  const handleBladeToggle = () => {
    const nextState = !bladeOn;
    setBladeOn(nextState);
    sendCommand(nextState ? "W" : "w");
  };

  return (
    <main className="scifi-container">
      <div className="ip-pair-row">
        <label htmlFor="ipInput" className="ip-label">
          ESP8266 IP:
        </label>
        <input
          id="ipInput"
          type="text"
          value={ip}
          onChange={(e) => setIp(e.target.value)}
          className="ip-input"
          placeholder="e.g. 192.168.4.1"
          disabled={pairing}
        />
        <button
          className="pair-btn"
          onClick={handlePair}
          disabled={pairing}
          aria-label="Pair button"
        >
          {pairing ? "Pairing..." : "Pair"}
        </button>
      </div>

      {/* Controller always visible */}
      <div className="circle-pad">
        <button className="arrow-btn arrow-up" onClick={() => sendCommand("F")}>
          ↑
        </button>
        <button
          className="arrow-btn arrow-left"
          onClick={() => sendCommand("L")}
        >
          ←
        </button>
        <button className="arrow-btn stop-btn" onClick={() => sendCommand("S")}>
          ■
        </button>
        <button
          className="arrow-btn arrow-right"
          onClick={() => sendCommand("R")}
        >
          →
        </button>
        <button
          className="arrow-btn arrow-down"
          onClick={() => sendCommand("B")}
        >
          ↓
        </button>
      </div>

      <div className="blade-control">
        <span className="blade-label">Blade</span>
        <label className="switch">
          <input
            type="checkbox"
            checked={bladeOn}
            onChange={handleBladeToggle}
          />
          <span className="slider" />
        </label>
        <span className={`blade-status ${bladeOn ? "on" : "off"}`}>
          {bladeOn ? "ON" : "OFF"}
        </span>
      </div>

      <p className="status-message">{status}</p>
    </main>
  );
}
