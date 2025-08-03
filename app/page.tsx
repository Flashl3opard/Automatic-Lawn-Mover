"use client";
import { useState } from "react";
import axios from "axios";

export default function Home() {
  const [ip, setIp] = useState("192.168.4.1");
  const [status, setStatus] = useState("");

  const sendCommand = async (cmd: string) => {
    try {
      await axios.get(`http://${ip}/?State=${cmd}`);
      setStatus(`✅ Command Sent: ${cmd}`);
    } catch {
      setStatus(`❌ Failed to send: ${cmd}`);
    }
  };

  return (
    <main className="min-h-screen bg-gradient-to-br from-gray-900 to-gray-800 text-white p-6 flex flex-col items-center">
      <h1 className="text-3xl font-bold mb-4">Lawn Mower Remote</h1>

      <input
        type="text"
        value={ip}
        onChange={(e) => setIp(e.target.value)}
        className="bg-blue-100/10 backdrop-blur-md border border-blue-400 text-blue-200 placeholder-blue-300 px-4 py-2 rounded-xl w-full max-w-xs mb-6 focus:outline-none focus:ring-2 focus:ring-blue-500 transition"
        placeholder="Enter ESP8266 IP (e.g. 192.168.4.1)"
      />

      {/* Movement Controls */}
      <div className="grid grid-cols-3 gap-4 mb-8">
        <div></div>
        <button className="btn-dir" onClick={() => sendCommand("F")}>
          ▲
        </button>
        <div></div>

        <button className="btn-dir" onClick={() => sendCommand("L")}>
          ◀
        </button>
        <button className="btn-dir stop" onClick={() => sendCommand("S")}>
          ⏹
        </button>
        <button className="btn-dir" onClick={() => sendCommand("R")}>
          ▶
        </button>

        <div></div>
        <button className="btn-dir" onClick={() => sendCommand("B")}>
          ▼
        </button>
        <div></div>
      </div>

      {/* Blade Controls */}
      <div className="flex flex-col items-center gap-4 mb-6">
        <div className="flex gap-4">
          <button className="btn-blade-on" onClick={() => sendCommand("W")}>
            Blade ON
          </button>
          <button className="btn-blade-off" onClick={() => sendCommand("w")}>
            Blade OFF
          </button>
        </div>

        <div className="grid grid-cols-6 gap-2">
          {[..."0123456789q"].map((val) => (
            <button
              key={val}
              className="btn-speed"
              onClick={() => sendCommand(val)}
            >
              {val}
            </button>
          ))}
        </div>
      </div>

      {/* Status */}
      <p className="text-sm text-green-400">{status}</p>
    </main>
  );
}
