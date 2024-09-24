var dt = new Date(), i = 0;

while (true) {
	if (i > 3) {
		break;
	}
	dt = new Date();
	WScript.Echo("Tick(2): " + dt.getHours() + ":" + dt.getMinutes() + ":" + dt.getSeconds());
	WScript.sleep(1000);
	++i;
}