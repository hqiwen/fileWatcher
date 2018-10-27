"use strict"

const EventEmitter = require('events').EventEmitter;
const path = require("path");
const fs = require("fs");
const EFSWCore = require("../build/Release/core").EFSWCore;

const ACTION_MAP = {
    "1": "ADD",
    "2": "DELETE",
    "3": "MODIFIED",
    "4": "MOVED"
};

class Watcher extends EventEmitter{
    constructor(_path) {
        _path = path.resolve(process.cwd(), _path);
        super();
        Object.defineProperties(this, {
            path: {
                value: _path,
                configurable: false,
                enumerable: true,
                writable: false
            },
            core: {
                value: new EFSWCore(_path, this._onEFSWEvent.bind(this)),
                configurable: false,
                enumerable: false,
                writable: false
            }
        });

        this.watching = false;
    }

    _onEFSWEvent(_path, filename, oldFilename, action) {
        const fullPath = path.join(_path, filename);
        const info = {
            dir: _path,
            action: ACTION_MAP[action] || "UNKNOWN",
            relative: filename
        };
        
        if (oldFilename) {
            info.old = path.join(_path, oldFilename);
            info.oldRelative = oldFilename;
        }

        if (info.action === "UNKNOWN") {
            const err = new Error(`Unknown fs event ${action}.`);
            err.info = info;
            this.emit("error", err);
        } else {
            this.emit("change", fullPath, info);
        }
    }

    start() {
        if (this.watching) {
            return this.emit("error", new Error("Watcher is already in watching"));
        }

        try {
            this.core.start();
        } catch (error) {
            return this.emit("error", error);
        }
        this.watching = true;
    }

    stop() {
        this.core.stop();
        this.watching = false;
    }
};

module.exports = Watcher;