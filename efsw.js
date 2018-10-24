const Watcher = require('efsw').Watcher
const watcher = new Watcher(_dirname)
watcher.on('change', function (path, info) {
    console.log(path, info.action, info.old);
})