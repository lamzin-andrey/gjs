    function initOnLoad(sElementName) {
        var oElement = (sElementName == "body") ? document[sElementName] :
        document.getElementById(sElementName);
        if(oElement != null && typeof(oElement) != "undefined") { initpan2(); }
          else { setTimeout(function() { initOnLoad(sElementName); }, 20); }
    }
   function me(tt, nn)
    {
       var id=tt.style;
       if (typeof(id.textShadow) != 'undefined')
       {
          id.textShadow=( nn == 0 )? '1px 1px 1px #88AEFF' : '';
       }
    }
    function initpan2()
    {
        var ppp=document.getElementById('kjhgfdsa');
        if (typeof(ppp.style.opacity) != 'undefined')
        {
            ppp.onmouseover=function() { ch_opacity(1);};
            ppp.onmousout  =function() { ch_opacity(0);};
            ppp.style.opacity="0.8";
        }
        if (typeof(ppp.style.borderRadius) === "string")
        {
           ppp.style.borderRadius="6px";
           document.getElementById('container').style.borderRadius="9em / 1em";
           //document.getElementById('content').style.borderRadius="0em 9em 9em 0em /1em";
           var pcontent=document.getElementById('content').style;
           pcontent.borderTopRightRadius="9em  1em";
           pcontent.borderBottomRightRadius="9em  1em";

           var divs=document.getElementsByTagName("DIV");
           for( var i=0; i<divs.length; i++)
               if(divs[i].className.substr(0,6) == "primer")
                  divs[i].style.borderRadius="1em";
        }
    }
    function ch_opacity(par)
    {
        var zzz=document.getElementById('kjhgfdsa');
        if (typeof(zzz.style.opacity) != 'undefined')
        {
            zzz.style.opacity= ( par == 1) ? "1" : "0.8";
        }
     }
    initOnLoad("kjhgfdsa");