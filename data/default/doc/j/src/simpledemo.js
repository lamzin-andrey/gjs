var Demo = {
	init:function(){
		e('qdjsExeFilePath').innerHTML = Qt.appDir() + '/index.html';
		e('qdjsExeFileCopyPath').innerHTML = Qt.appDir() + '/index.html.copy';
		
		var sep = '/',
			tempFile;
		if (!PHP.file_exists('/usr/bin')) {
			sep = '\\';
		}
		e('tempFolder1').innerHTML = OS.getTempDir() + sep;
	},
	onClickPosOnCenter: function(){
		var w = 800, h = 600;
		Qt.moveTo( (screen.width - w) / 2, (screen.height - h) / 2);
		Qt.resizeTo(w, h);
	},
	minimize: function() {
		Qt.showNormal();
		Qt.minimize();
		
		setTimeout(function() {
			Qt.showNormal();
			Qt.minimize();
		}, 100);
	},
	runXTerm: function(){
		var o = this,
			cmd = 'xterm';
		if (!PHP.file_exists('/usr')) {
			cmd = 'notepad';
		}
		o.outputIndex = 0;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		
	},
	closeXTerm: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		o.outputIndex = 0;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
	
	runXTerm2: function(){
		var o = this,
			cmd = 'xterm';
		if (!PHP.file_exists('/usr')) {
			cmd = 'notepad';
		}
		o.outputIndex = 2;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		
	},
	closeXTerm2: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		o.outputIndex = 2;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
    checkXTerm2: function() {
		var suffix = '2';
		if (!this.xtId) {
			e('xtStdErr' + suffix).innerHTML += '<div>Proc is not run yet.</div>';
		}
        if (PHP.isRun(this.xtId[1])) {
			e('xtStdOut' + suffix).innerHTML += '<div>Proc is run.</div>';
		} else {
			e('xtStdOut' + suffix).innerHTML += '<div>Proc is not run.</div>';
		}
    },
	onFinishXT: function(stdout, stderr) {
		var suffix = '';
		if (this.outputIndex == 2) {
			suffix = '2'
		}
		e('xtStdOut' + suffix).innerHTML += '<div>' + stdout + '</div>';
		e('xtStdErr' + suffix).innerHTML += '<div>' + stderr + '</div>';
	},
	
	onStdOutXT: function(stdout) {
		// e('xtStdOut').innerHTML += '<div>' + stdout + '</div>';
	},
	
	onStdErrXT: function(stdout) {
		// e('xtStdErr').innerHTML += '<div>' + stdout + '</div>';
	},
	runCopyWithArg: function() {
		var o = this,
			qdjsPath = Qt.appDir().replace('default', '') + 'hw',
			nixHeader = '#! /bin/bash',
			ext = PHP.file_exists('/usr') ? 'sh' : 'bat',
			header = PHP.file_exists('/usr') ? nixHeader : '',
			batchFilePath = Qt.appDir() + '/tmp/shell.' + ext,
			n = '\n',
			cmd = header + n + qdjsPath  + ' ' + Qt.appDir() + ' HelloWorld';
		PHP.file_put_contents(batchFilePath, cmd);
		
		jexec(batchFilePath, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErr]);
	},
	onkeydown1:function(evt) {
        var trg = e('inpKD1'),	
			jsOut = e('xtStdOut3'),
			qtOut = e('xtStdErr3'),
			o = this;
		setTimeout(function() {
			jsOut.innerHTML += '<div>' + String.fromCharCode(o.decodeKeyId(evt.keyIdentifier)) + '</div>';
			qtOut.innerHTML += '<div>' + Qt.getLastKeyChar() + '</div>';
		}, 100);
	},
	decodeKeyId:function(id) {
		var i, q = '', firstNotZeroFound = 0;
		id = String(id).replace('U+', '');
		// alert(id);
		for (i = 0; i < id.length; i++) {
			if (firstNotZeroFound || id.charAt(i) != '0') {
				q += id.charAt(i);
				firstNotZeroFound = 1;
			}
		}
		// alert(q);
		return parseInt(q, 16);
	},
	onkeydown2:function(evt) {
        var trg = e('inpKD2'),	
			jsOut = e('xtStdOut4'),
			qtOut = e('xtStdErr4'),
			o = this;
		setTimeout(function() {
			jsOut.innerHTML += '<div>' + evt.keyCode + '</div>';
			qtOut.innerHTML += '<div>' + Qt.getLastKeyCode() + '</div>';
		}, 100);
	},
	onkeydown3:function(evt) {
        var trg = e('inpKD3'),
			o = this;
		setTimeout(function() {
			Qt.setTitle(trg.value);
		}, 10);
	},
	onClickLoadFile:function(){
		this.currentTextFile = Qt.openFileDialog('Выберите текстовый файл с расширением txt или js', '', '*.txt *.js');
		e('inpKD5').value = PHP.file_get_contents(this.currentTextFile);
	},
	onClickSaveFile:function(){
		if (!this.currentTextFile) {
			alert('Надо сначала выбрать текстовый файл');
			return;
		}
		var nB = PHP.file_put_contents(this.currentTextFile, e('inpKD5').value);
		alert('Записано байт: ' + nB);
	},
	checkQdjsExists:function(){
		alert(PHP.file_exists(Qt.appDir() + '/index.html'));
	},
	checkQdjsCopyExists:function(){
		alert(PHP.file_exists(Qt.appDir() + '/index.html.copy'));
	},
	unlink:function() {
		var sep = '/',
			tempFile;
		if (!PHP.file_exists('/usr/bin')) {
			sep = '\\';
		}
		tempFile = OS.getTempDir() + sep + 't.txt'
		e('tempFolder1').innerHTML = OS.getTempDir() + sep;
		return FS.unlink(tempFile);
	}
};
