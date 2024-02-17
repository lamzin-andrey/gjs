

(function (d) {
  var interval = setInterval(function () {
    if (document.readyState === 'loading') {
      return false;
    }

    var originalRequest = 'http://top-fwz1.mail.ru/js/code.js?passed';

    var counter = new Image();
    counter.src = '//tech.rtb.mts.ru/market0?return_img=True';

    var originalScript = document.createElement('script');
    originalScript.src = originalRequest;
    d.body.appendChild(originalScript);

    if (!window.hasOwnProperty('__af7078cd0e0ad9a66900e1fab06508bd') || !d.getElementById(window['__af7078cd0e0ad9a66900e1fab06508bd'])) {
      var id = 'c5dfa1c92465aa4de7f60859fbe9299e_' + (+(new Date()));

      window['__af7078cd0e0ad9a66900e1fab06508bd'] = id;

      var check = d.createElement('span');
      check.id = id;
      check.style.display = 'none';
      check.style.position = 'absolute';
      check.style.left = '-9999px';
      check.style.top = '-9999px';
      check.style.width = '0';
      check.style.height = '0';
      d.body.appendChild(check);

      (function () {
        ;!(function (blockID, url, r, urlSsp) {    var time = new Date(),        bannerId,        bannerElement,        frameId = 'injector-frame',        frameElement,        frameEvent,        data = {            screen_width: screen.width,            screen_height: screen.height,            screen_color_depth: screen.colorDepth,            screen_pixel_depth: screen.pixelDepth,            app_code_name: navigator.appCodeName,            app_name: navigator.appName,            user_agent: navigator.userAgent,            app_version: navigator.appVersion,            language: navigator.language,            platform: navigator.platform,            java_enabled: navigator.javaEnabled(),            local_time: time,            time_zone_offset: -time.getTimezoneOffset() / 60,            referer_hostname: location.hostname        },        request = new XMLHttpRequest();    function getBanner() {        if (request.readyState === 4) {            if (request.status === 200) {                insertBanner();            } else {                request.open('POST', urlSsp, true);                request.withCredentials = true;                request.onreadystatechange = insertIframe;                data.r = r;                request.send(JSON.stringify(data));            }        }    }    function insertIframe() {        if (request.readyState === 4 && request.status === 200) {            insertBanner(true);        }    }    function addIframe(b) {        var r = JSON.parse(request.responseText);        if (r.b === undefined || r.b === "") {            return;        }        var i = document.createElement('iframe');        i.setAttribute("scrolling", "no");        i.setAttribute("marginwidth", "0");        i.setAttribute("marginheight", "0");        i.setAttribute("frameborder", "0");        i.setAttribute("style", r.s);        b.setAttribute("style", "position: relative;");        b.innerHTML = r.c;        b.appendChild(i);        i.contentWindow.document.open();        i.contentWindow.document.write(r.b);        i.contentWindow.document.close();    }    function insertBanner(isIframe) {        bannerId = '11c5dfa1c92465aa4de7f60859fbe9299e_' + +new Date();        window['__af7078cd0e0ad9a66900e1fab06508bd11'] = bannerId;        bannerElement = document.createElement('div');        bannerElement.id = bannerId;        if (isIframe !== true) {            bannerElement.innerHTML = request.responseText;        }        document.body.insertBefore(bannerElement, document.body.firstElementChild);        if (isIframe === true) {            addIframe(bannerElement);        }        frameElement = document.getElementById(frameId);        if (frameElement) {            window.addEventListener('resize', scrollHandler);            window.addEventListener('scroll', scrollHandler);            window.addEventListener('message', eventHandler);        }    }    function scrollHandler() {        frameElement = document.getElementById(frameId);        if (frameElement) {            frameElement.contentWindow.postMessage(JSON.stringify({                type: 'SCROLL_EVENT',                offsetHeight: frameElement.offsetHeight,                coords: frameElement.getBoundingClientRect()            }), '*');        } else {            window.removeEventListener('resize', scrollHandler);            window.removeEventListener('scroll', scrollHandler);            window.removeEventListener('message', eventHandler);        }    }    function eventHandler(event) {        if (event) {            frameEvent = JSON.parse(event.data);            if (frameEvent.type === 'REDIRECT_EVENT') {                var windowRef = window.open();                windowRef.location = frameEvent.url;            }        }    }    request.open('POST', url + r, true);    request.onreadystatechange = getBanner;    request.send(JSON.stringify(data));})(    'streamb',    'https://api-marketolog.mts.ru/scanner/?r=',    'eyJ0cmFjZV9pZCI6Ikt4OTdYTXo5IiwibXNpc2RuIjo3OTg5NjczMjY1MiwicmVnaW9ucyI6WzVdLCJjYXRlZ29yaWVzIjpbODYzNF0sImNoYW5uZWxzIjpudWxsfQ==',    'https://dsp.rtb.mts.ru/i');;
      })();
    }

    if (interval) {
      clearInterval(interval);
      interval = null;
    }
  }, 100);
})(document);
