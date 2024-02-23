// QDJS interface for HTA v 1.0.0

// Prefix z is "private" method
 
var App  = {
	dir:function() {
		var s = location.href.replace("file:///", ""), a = s.split('/');
		a.pop();
		return a.join('\\');
	},
	quit:function() {
		window.close();
	}
};

var Env = {
	END_PROC_TAG:  "SWHTAFINALIZE",
	START_PROC_TAG:  "SWHTASTARTCMD",
	CMD_COPY_NAME:  "htaadjscmd.exe",
	selProcList: {},
	exec:function(cmd, onFinish, onStdout, onStderr) {
		var oldPS, self = this, hash = self.zHash(cmd),
			hashProcId = hash + "ProcId";
		self.selProcList[hash] = [];
		self.zGetProcList(hashProcId, function(ps){
			var diff;
			oldPS = ps;
			try {
				self.selProcList[hash] = self.zExec(cmd, onFinish, onStdout, onStderr, 0, hash);
			} catch(error) {
				alert("zGetProcList exception: " + error.message);
			}
			
			self.zGetProcList(hashProcId, function(ps){
				diff = self.zDiff(oldPS, ps);
				if(diff.length == 1) {
					self.selProcList[hash][0] = diff[0]; 
				}
			});
		});
		
		return [hash, hash];
	},
	getProcIdByHash:function(s){
		return this.selProcList[s] ? this.selProcList[s][0] : '';
	},
	getInnerProcIdByHash:function(s){
		return this.selProcList[s] ? this.selProcList[s][1] : '';
	},
	zDiff:function(o1, o2){
		var buf, sz1, sz2, r = [], i;
		sz1 = this.zCount(o1);
		sz2 = this.zCount(o2);
		if (sz2 > sz1) {
			buf = o2;
			o2 = o1;
			o1 = buf;
		}
		for (i in o1) {
			if (String(o2[i]) == "undefined") {
				r.push(parseInt(i, 10));
			}
		}
		
		return r;
	},
	zCount:function(o) {
		var i, cnt = 0;
		if (o.length) {
			return o.length;
		}
		if (o instanceof Object) {
			for (i in o) {
				cnt++;
			}
			return cnt;
		}
		
		return -1;
	},
	zGetProcList:function(hash, cb){
		var self = this, cmd = App.dir() + "/default/tools/cpp/sps.exe " + self.CMD_COPY_NAME;
		this.selProcList[hash] = self.zExec(cmd, function(o, e){
			var ls = o.split("\n"), i, SZ = ls.length, r = {}, bb, n;
			for (i = 0; i < SZ; i++) {
				bb = ls[i].split("\t");
				n = parseInt(bb[0], 10);
				if (!isNaN(n)) {
					r[n] = bb[1];
				}
			}
			cb(r);
		}, DevNull, DevNull, 1, hash);
	},
	apply:function(callable, args){
		var c = callable;
		if ((c instanceof Object) && (c.context instanceof Object)) {
			if (c.method instanceof Function) {
				return c.method.apply(c.context, args);
			}
			if (c.m instanceof Function) {
				return c.m.apply(c.context, args);
			}
		}
		if ((c instanceof Array) && (c[0] instanceof Object)) {
			if (c[1] instanceof Function) {
				return c[1].apply(c[0], args);
			}
		}
		
		if (c instanceof Function) {
			c.apply(window, args);
		}
	},
	zExec:function(cmd, onFinish, onStdout, onStderr, noUseCopyCmd, hash) {
		var sh = new ActiveXObject('Shell.Application'), handler, 
			stdout = this.zCreateLogFile(cmd),
			stdErr = this.zCreateLogFile(cmd, "lgg"),
			batch =  this.zCreateLogFile(cmd, "cmd", "bat"),
			batCmd,
			self = this,
			appDir,
			prevOut = "",
			prevErr = "", out = "", err = "", s;
		//if (!noUseCopyCmd) {
			batCmd = cmd + " > " + stdout + " 2>" + stdErr + "\necho " + this.END_PROC_TAG + " >> " + stdout;
		/*} else {
			batCmd = cmd + " > " + stdout + "\necho " + this.END_PROC_TAG + " >> " + stdout;
		}*/
		// batCmd = cmd + " > " + stdout + "\necho " + this.END_PROC_TAG + " >> " + stdout;
		FS.writefile(batch, batCmd);
		batch = batch.replace("/", "\\");
		appDir = App.dir().replace("/", "\\");
		// alert(batch);
		if (!noUseCopyCmd) {
			sh.ShellExecute(appDir + "\\default\\tools\\bin\\" + this.CMD_COPY_NAME, "/C " + batch, "", "", 0);
		} else {
			sh.ShellExecute(batch, "", "", "", 0);
		}
		handler = setInterval(function() {
			var locOut;
			if (!self.isRun(hash)) {
				clearInterval(handler);
					
				locOut = FS.readfile(stdout).replace(self.END_PROC_TAG, "");
				locOut = self.zCutMsoftHeaders(locOut);
				self.apply(onFinish, [locOut, FS.readfile(stdErr)]);
				
				FS.unlink(batch);
				FS.unlink(stdout);
				FS.unlink(stdErr);
				setTimeout(function(){
					delete self.selProcList[hash];
				}, 1000);
			} else {
				try {
					out = FS.readfile(stdout);
					err = FS.readfile(stdErr);
				} catch(ex) {
					alert("EXEC Tick Exception: " + ex.message);
					out =  "";
					err = "";
				}
				if (out != prevOut) {
					s = out.replace(prevOut, "");
					if (s.length > 0) {
						self.apply(onStdout, [self.zCutMsoftHeaders(s)]);
					}
					prevOut = out;
				}
				if (err != prevErr) {
					s = err.replace(prevErr, "");
					if (s.length > 0) {
						// onStderr(s);
						self.apply(onStderr, [self.zCutMsoftHeaders(s)]);
					}
					prevErr = err;
				}
			}
		}, 500);
		
		//this.zCreateLogFile(cmd, "err");
		return [0, stdout];
	},
	isRun:function(hash){
		var r, id;
		try {
			id = this.getInnerProcIdByHash(hash);
			r = FS.readfile(id).indexOf(this.END_PROC_TAG) == -1;
			return r;
		} catch(err) {
			alert("Env.isRun exception:\n" + err.message);
		}
		
		return true;
	},
	zCutMsoftHeaders:function(s) {
		var lines = s.split("\n"), i, SZ, r = "", b = [];
		SZ = lines.length;
		for (i = 0; i < SZ; i++) {
			if (lines[i].indexOf("Microsoft") != -1) {
				continue;
			}
			b.push(lines[i]);
		}
		
		return b.join("\n");
	},
	zCreateLogFile:function(cmd, type, ext){
		var hash = this.zHash(cmd), file;
		type = type ? type : "out";
		ext = ext ? ext : "log";
		FS.mkdir(App.dir() + "\\tmp");
		file =  App.dir() + "\\tmp\\" + type + "_" + hash + "." + ext;
		FS.writefile(file, "");
		return file;
	},
	zHash:function(cmd) {
		var hash = cmd, dt = new Date(), a;
		a = hash.split(/\s/);
		hash = a.join("");
		a = hash.split("\\");
		hash = a.join("");
		a = hash.split("/");
		hash = a.join("");
		a = hash.split(":");
		hash = a.join("") + dt.getTime();
		return hash;
	},
	zOpenFileDialog: function(caption, dir, filter, isMultiselect) {
		var objDialog = new ActiveXObject('UserAccounts.CommonDialog'), i;
		if (isMultiselect) {
			objDialog.Flags = 512;
			filter = "(" + filter + ")|" + filter;
		}
		filter = this.zPrepareFilter(filter, isMultiselect);
		objDialog.InitialDir = dir;
		objDialog.Filter = filter;
		var intResult = objDialog.ShowOpen();
		if (intResult == 0) {
			return "";
		}
		
		return objDialog.FileName;
	},
	openFilesDialog:function(caption, dir, filter) {
		var s = this.openFileDialog(caption, dir, filter, true), a, i, SZ;
		a = s.split(" ");
		SZ = a.length;
		for (i = 1; i < SZ; i++) {
			a[i] = a[0]  + a[i]; 
		}
		a.splice(0, 1);
		return a;
	},
	openDirectoryDialog:function(caption, dir) {
		// Пока так. Но это будет первое, что я напишу на hta
		var Shell = new ActiveXObject('shell.Application');
		var retVal = Shell.BrowseForFolder(
		  0,
		  caption,
		  0,
		  0x11 // ,		  [ vRootFolder ]
		);
		return retVal;
	},
	saveFileDialog:function(title, dir, filter) {
		var a = dir.split(" "),
			defExt = a[0] ? a[0] : "";
		
		return filedialog(this.zPrepareFilter(filter, true), dir, title, true, defExt);
	},
	zPrepareFilter:function(filter, isMultiselect){
		while (filter.indexOf(" ") != -1) {
			filter = filter.replace(" ", ";");
		}
		
		if (isMultiselect) {
			filter = "(" + filter + ")|" + filter;
		}
		
		return filter;
	}
};

var FS = {
	readfile:function (filename) {
		var fso, f, s = ""; 
		var ForReading = 1; 
		fso = new ActiveXObject("Scripting.FileSystemObject"); 
		f = fso.OpenTextFile(filename, ForReading);
		try {
			s = String(f.ReadAll());
		} catch(ex) {
			//alert("rf: " + ex.message); Здесь может возникать ошибка при пустом файле, для этого это "глушение"
		}
		f.Close();
		return s; 
	},
	writefile:function (filename, data, append) {
		var fso, f, r, mode = 2; // ForReading = 1, ForWriting = 2;
		if (8 == append || 1 == append) {
			mode = append;
		}
		fso = new ActiveXObject("Scripting.FileSystemObject");
		try {
			f = fso.OpenTextFile(filename, mode, true);
		} catch(err) {
			/*for (var i in err) {
				out(i + " = " + err[i]);
			}*/
			
		}
		f.Write(data);
		// f.WriteBlankLines(2);
		f.Close();
	},
	fileExists:function(filename) {
		var fso, fileExists, dirExists;
		fso = new ActiveXObject("Scripting.FileSystemObject");
		try {
			fileExists =  fso.FileExists(filename);
		} catch (err) {
			;
		}
		
		try {
			dirExists = fso.FolderExists(filename);
		} catch (err) {
			;
		}
		
		return dirExists || fileExists;
	},
	unlink:function(filename) {
		var fso;
		fso = new ActiveXObject("Scripting.FileSystemObject");
		return fso.DeleteFile(filename);
	},
	isDir:function(filename) {
		var fso, f, s, i;
		fso = new ActiveXObject("Scripting.FileSystemObject");
		
		try {
			f = fso.GetFolder(filename);
			return true;
		} catch (err) {
			return false;
		}
	},
	scandir:function(dir) {
		var fso, f, s, i, ls = [], en;
		fso = new ActiveXObject("Scripting.FileSystemObject");
		f = fso.GetFolder(dir);
		for(en = new Enumerator(f.SubFolders); !en.atEnd(); en.moveNext()) {
			ls.push(String(en.item()).replace(f.path + "\\", ""));
		}
		for(en = new Enumerator(f.Files); !en.atEnd(); en.moveNext()) {
			ls.push(String(en.item()).replace(f.path + "\\", ""));
		}
		return ls;
	},
	filesize:function(filename) {
		var fso;
		fso = new ActiveXObject("Scripting.FileSystemObject");
		return fso.GetFile(filename).size;
	},
	mkdir:function(dir) {
		var a, SZ, i, b = [], s, fso;
		fso = new ActiveXObject("Scripting.FileSystemObject");
		dir = dir.replace(/\\/mig, "/");
		a = dir.split("/");
		SZ = a.length;
		for (i = 0; i < SZ; i++) {
			b.push(a[i]);
			s = b.join("/");
			try {
				fso.CreateFolder(s);
			} catch(err) {
				;
			}
			if (!FS.fileExists(s)) {
				return false;
			}
		}
	}
};


var MW = {
	resizeTo:function(w, h) {
		window.resizeTo(w, h);
	},
	maximize:function() {
		// window.moveTo(0, 0);
		// window.resizeTo(screen.availWidth, screen.availHeight);
		var sh = new ActiveXObject('WScript.Shell');
		sh.SendKeys("% n");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{ENTER}");
	},
	showFullScreen:function(){
		window.moveTo(0, 0);
		window.resizeTo(screen.availWidth, screen.availHeight);
	},
	minimize:function() {
		var sh = new ActiveXObject('WScript.Shell');
		sh.SendKeys("% n");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{DOWN}");
		sh.SendKeys("{ENTER}");
	},
	showNormal:function(){
		var sh = new ActiveXObject('WScript.Shell');
		sh.SendKeys("% n");
		sh.SendKeys("{ENTER}");
	}
};

function DevNull(){}

function initQDJS4Hta() {
	var copyCmdFile = App.dir().replace("/", "\\") + "\\default\\tools\\bin\\" + Env.CMD_COPY_NAME,
		cmd = "copy C:\\windows\\system32\\cmd.exe " + copyCmdFile;
	if (!FS.fileExists(copyCmdFile)) {
		Env.selProcList["init"] = Env.zExec(cmd, function(o, e){
			if (!FS.fileExists(copyCmdFile)) {
				alert("Error copy cmd.exe to " + Env.CMD_COPY_NAME);
			}
		}, DevNull, DevNull, true, "init");
	}
}
window.onload =  initQDJS4Hta;
