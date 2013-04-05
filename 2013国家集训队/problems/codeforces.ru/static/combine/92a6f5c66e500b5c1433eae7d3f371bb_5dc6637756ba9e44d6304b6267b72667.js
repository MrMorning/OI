var q=null;window.PR_SHOULD_USE_CONTINUATION=!0;
(function(){function L(a){function m(a){var f=a.charCodeAt(0);if(f!==92)return f;var b=a.charAt(1);return(f=r[b])?f:"0"<=b&&b<="7"?parseInt(a.substring(1),8):b==="u"||b==="x"?parseInt(a.substring(2),16):a.charCodeAt(1)}function e(a){if(a<32)return(a<16?"\\x0":"\\x")+a.toString(16);a=String.fromCharCode(a);if(a==="\\"||a==="-"||a==="["||a==="]")a="\\"+a;return a}function h(a){for(var f=a.substring(1,a.length-1).match(/\\u[\dA-Fa-f]{4}|\\x[\dA-Fa-f]{2}|\\[0-3][0-7]{0,2}|\\[0-7]{1,2}|\\[\S\s]|[^\\]/g),a=
[],b=[],o=f[0]==="^",c=o?1:0,i=f.length;c<i;++c){var j=f[c];if(/\\[bdsw]/i.test(j))a.push(j);else{var j=m(j),d;c+2<i&&"-"===f[c+1]?(d=m(f[c+2]),c+=2):d=j;b.push([j,d]);d<65||j>122||(d<65||j>90||b.push([Math.max(65,j)|32,Math.min(d,90)|32]),d<97||j>122||b.push([Math.max(97,j)&-33,Math.min(d,122)&-33]))}}b.sort(function(a,f){return a[0]-f[0]||f[1]-a[1]});f=[];j=[NaN,NaN];for(c=0;c<b.length;++c)i=b[c],i[0]<=j[1]+1?j[1]=Math.max(j[1],i[1]):f.push(j=i);b=["["];o&&b.push("^");b.push.apply(b,a);for(c=0;c<
f.length;++c)i=f[c],b.push(e(i[0])),i[1]>i[0]&&(i[1]+1>i[0]&&b.push("-"),b.push(e(i[1])));b.push("]");return b.join("")}function y(a){for(var f=a.source.match(/\[(?:[^\\\]]|\\[\S\s])*]|\\u[\dA-Fa-f]{4}|\\x[\dA-Fa-f]{2}|\\\d+|\\[^\dux]|\(\?[!:=]|[()^]|[^()[\\^]+/g),b=f.length,d=[],c=0,i=0;c<b;++c){var j=f[c];j==="("?++i:"\\"===j.charAt(0)&&(j=+j.substring(1))&&j<=i&&(d[j]=-1)}for(c=1;c<d.length;++c)-1===d[c]&&(d[c]=++t);for(i=c=0;c<b;++c)j=f[c],j==="("?(++i,d[i]===void 0&&(f[c]="(?:")):"\\"===j.charAt(0)&&
(j=+j.substring(1))&&j<=i&&(f[c]="\\"+d[i]);for(i=c=0;c<b;++c)"^"===f[c]&&"^"!==f[c+1]&&(f[c]="");if(a.ignoreCase&&s)for(c=0;c<b;++c)j=f[c],a=j.charAt(0),j.length>=2&&a==="["?f[c]=h(j):a!=="\\"&&(f[c]=j.replace(/[A-Za-z]/g,function(a){a=a.charCodeAt(0);return"["+String.fromCharCode(a&-33,a|32)+"]"}));return f.join("")}for(var t=0,s=!1,l=!1,p=0,d=a.length;p<d;++p){var g=a[p];if(g.ignoreCase)l=!0;else if(/[a-z]/i.test(g.source.replace(/\\u[\da-f]{4}|\\x[\da-f]{2}|\\[^UXux]/gi,""))){s=!0;l=!1;break}}for(var r=
{b:8,t:9,n:10,v:11,f:12,r:13},n=[],p=0,d=a.length;p<d;++p){g=a[p];if(g.global||g.multiline)throw Error(""+g);n.push("(?:"+y(g)+")")}return RegExp(n.join("|"),l?"gi":"g")}function M(a){function m(a){switch(a.nodeType){case 1:if(e.test(a.className))break;for(var g=a.firstChild;g;g=g.nextSibling)m(g);g=a.nodeName;if("BR"===g||"LI"===g)h[s]="\n",t[s<<1]=y++,t[s++<<1|1]=a;break;case 3:case 4:g=a.nodeValue,g.length&&(g=p?g.replace(/\r\n?/g,"\n"):g.replace(/[\t\n\r ]+/g," "),h[s]=g,t[s<<1]=y,y+=g.length,
t[s++<<1|1]=a)}}var e=/(?:^|\s)nocode(?:\s|$)/,h=[],y=0,t=[],s=0,l;a.currentStyle?l=a.currentStyle.whiteSpace:window.getComputedStyle&&(l=document.defaultView.getComputedStyle(a,q).getPropertyValue("white-space"));var p=l&&"pre"===l.substring(0,3);m(a);return{a:h.join("").replace(/\n$/,""),c:t}}function B(a,m,e,h){m&&(a={a:m,d:a},e(a),h.push.apply(h,a.e))}function x(a,m){function e(a){for(var l=a.d,p=[l,"pln"],d=0,g=a.a.match(y)||[],r={},n=0,z=g.length;n<z;++n){var f=g[n],b=r[f],o=void 0,c;if(typeof b===
"string")c=!1;else{var i=h[f.charAt(0)];if(i)o=f.match(i[1]),b=i[0];else{for(c=0;c<t;++c)if(i=m[c],o=f.match(i[1])){b=i[0];break}o||(b="pln")}if((c=b.length>=5&&"lang-"===b.substring(0,5))&&!(o&&typeof o[1]==="string"))c=!1,b="src";c||(r[f]=b)}i=d;d+=f.length;if(c){c=o[1];var j=f.indexOf(c),k=j+c.length;o[2]&&(k=f.length-o[2].length,j=k-c.length);b=b.substring(5);B(l+i,f.substring(0,j),e,p);B(l+i+j,c,C(b,c),p);B(l+i+k,f.substring(k),e,p)}else p.push(l+i,b)}a.e=p}var h={},y;(function(){for(var e=a.concat(m),
l=[],p={},d=0,g=e.length;d<g;++d){var r=e[d],n=r[3];if(n)for(var k=n.length;--k>=0;)h[n.charAt(k)]=r;r=r[1];n=""+r;p.hasOwnProperty(n)||(l.push(r),p[n]=q)}l.push(/[\S\s]/);y=L(l)})();var t=m.length;return e}function u(a){var m=[],e=[];a.tripleQuotedStrings?m.push(["str",/^(?:'''(?:[^'\\]|\\[\S\s]|''?(?=[^']))*(?:'''|$)|"""(?:[^"\\]|\\[\S\s]|""?(?=[^"]))*(?:"""|$)|'(?:[^'\\]|\\[\S\s])*(?:'|$)|"(?:[^"\\]|\\[\S\s])*(?:"|$))/,q,"'\""]):a.multiLineStrings?m.push(["str",/^(?:'(?:[^'\\]|\\[\S\s])*(?:'|$)|"(?:[^"\\]|\\[\S\s])*(?:"|$)|`(?:[^\\`]|\\[\S\s])*(?:`|$))/,
q,"'\"`"]):m.push(["str",/^(?:'(?:[^\n\r'\\]|\\.)*(?:'|$)|"(?:[^\n\r"\\]|\\.)*(?:"|$))/,q,"\"'"]);a.verbatimStrings&&e.push(["str",/^@"(?:[^"]|"")*(?:"|$)/,q]);var h=a.hashComments;h&&(a.cStyleComments?(h>1?m.push(["com",/^#(?:##(?:[^#]|#(?!##))*(?:###|$)|.*)/,q,"#"]):m.push(["com",/^#(?:(?:define|elif|else|endif|error|ifdef|include|ifndef|line|pragma|undef|warning)\b|[^\n\r]*)/,q,"#"]),e.push(["str",/^<(?:(?:(?:\.\.\/)*|\/?)(?:[\w-]+(?:\/[\w-]+)+)?[\w-]+\.h|[a-z]\w*)>/,q])):m.push(["com",/^#[^\n\r]*/,
q,"#"]));a.cStyleComments&&(e.push(["com",/^\/\/[^\n\r]*/,q]),e.push(["com",/^\/\*[\S\s]*?(?:\*\/|$)/,q]));a.regexLiterals&&e.push(["lang-regex",/^(?:^^\.?|[!+-]|!=|!==|#|%|%=|&|&&|&&=|&=|\(|\*|\*=|\+=|,|-=|->|\/|\/=|:|::|;|<|<<|<<=|<=|=|==|===|>|>=|>>|>>=|>>>|>>>=|[?@[^]|\^=|\^\^|\^\^=|{|\||\|=|\|\||\|\|=|~|break|case|continue|delete|do|else|finally|instanceof|return|throw|try|typeof)\s*(\/(?=[^*/])(?:[^/[\\]|\\[\S\s]|\[(?:[^\\\]]|\\[\S\s])*(?:]|$))+\/)/]);(h=a.types)&&e.push(["typ",h]);a=(""+a.keywords).replace(/^ | $/g,
"");a.length&&e.push(["kwd",RegExp("^(?:"+a.replace(/[\s,]+/g,"|")+")\\b"),q]);m.push(["pln",/^\s+/,q," \r\n\t\xa0"]);e.push(["lit",/^@[$_a-z][\w$@]*/i,q],["typ",/^(?:[@_]?[A-Z]+[a-z][\w$@]*|\w+_t\b)/,q],["pln",/^[$_a-z][\w$@]*/i,q],["lit",/^(?:0x[\da-f]+|(?:\d(?:_\d+)*\d*(?:\.\d*)?|\.\d\+)(?:e[+-]?\d+)?)[a-z]*/i,q,"0123456789"],["pln",/^\\[\S\s]?/,q],["pun",/^.[^\s\w"-$'./@\\`]*/,q]);return x(m,e)}function D(a,m){function e(a){switch(a.nodeType){case 1:if(k.test(a.className))break;if("BR"===a.nodeName)h(a),
a.parentNode&&a.parentNode.removeChild(a);else for(a=a.firstChild;a;a=a.nextSibling)e(a);break;case 3:case 4:if(p){var b=a.nodeValue,d=b.match(t);if(d){var c=b.substring(0,d.index);a.nodeValue=c;(b=b.substring(d.index+d[0].length))&&a.parentNode.insertBefore(s.createTextNode(b),a.nextSibling);h(a);c||a.parentNode.removeChild(a)}}}}function h(a){function b(a,d){var e=d?a.cloneNode(!1):a,f=a.parentNode;if(f){var f=b(f,1),g=a.nextSibling;f.appendChild(e);for(var h=g;h;h=g)g=h.nextSibling,f.appendChild(h)}return e}
for(;!a.nextSibling;)if(a=a.parentNode,!a)return;for(var a=b(a.nextSibling,0),e;(e=a.parentNode)&&e.nodeType===1;)a=e;d.push(a)}var k=/(?:^|\s)nocode(?:\s|$)/,t=/\r\n?|\n/,s=a.ownerDocument,l;a.currentStyle?l=a.currentStyle.whiteSpace:window.getComputedStyle&&(l=s.defaultView.getComputedStyle(a,q).getPropertyValue("white-space"));var p=l&&"pre"===l.substring(0,3);for(l=s.createElement("LI");a.firstChild;)l.appendChild(a.firstChild);for(var d=[l],g=0;g<d.length;++g)e(d[g]);m===(m|0)&&d[0].setAttribute("value",
m);var r=s.createElement("OL");r.className="linenums";for(var n=Math.max(0,m-1|0)||0,g=0,z=d.length;g<z;++g)l=d[g],l.className="L"+(g+n)%10,l.firstChild||l.appendChild(s.createTextNode("\xa0")),r.appendChild(l);a.appendChild(r)}function k(a,m){for(var e=m.length;--e>=0;){var h=m[e];A.hasOwnProperty(h)?window.console&&console.warn("cannot override language handler %s",h):A[h]=a}}function C(a,m){if(!a||!A.hasOwnProperty(a))a=/^\s*</.test(m)?"default-markup":"default-code";return A[a]}function E(a){var m=
a.g;try{var e=M(a.h),h=e.a;a.a=h;a.c=e.c;a.d=0;C(m,h)(a);var k=/\bMSIE\b/.test(navigator.userAgent),m=/\n/g,t=a.a,s=t.length,e=0,l=a.c,p=l.length,h=0,d=a.e,g=d.length,a=0;d[g]=s;var r,n;for(n=r=0;n<g;)d[n]!==d[n+2]?(d[r++]=d[n++],d[r++]=d[n++]):n+=2;g=r;for(n=r=0;n<g;){for(var z=d[n],f=d[n+1],b=n+2;b+2<=g&&d[b+1]===f;)b+=2;d[r++]=z;d[r++]=f;n=b}for(d.length=r;h<p;){var o=l[h+2]||s,c=d[a+2]||s,b=Math.min(o,c),i=l[h+1],j;if(i.nodeType!==1&&(j=t.substring(e,b))){k&&(j=j.replace(m,"\r"));i.nodeValue=
j;var u=i.ownerDocument,v=u.createElement("SPAN");v.className=d[a+1];var x=i.parentNode;x.replaceChild(v,i);v.appendChild(i);e<o&&(l[h+1]=i=u.createTextNode(t.substring(b,o)),x.insertBefore(i,v.nextSibling))}e=b;e>=o&&(h+=2);e>=c&&(a+=2)}}catch(w){"console"in window&&console.log(w&&w.stack?w.stack:w)}}var v=["break,continue,do,else,for,if,return,while"],w=[[v,"auto,case,char,const,default,double,enum,extern,float,goto,int,long,register,short,signed,sizeof,static,struct,switch,typedef,union,unsigned,void,volatile"],
"catch,class,delete,false,import,new,operator,private,protected,public,this,throw,true,try,typeof"],F=[w,"alignof,align_union,asm,axiom,bool,concept,concept_map,const_cast,constexpr,decltype,dynamic_cast,explicit,export,friend,inline,late_check,mutable,namespace,nullptr,reinterpret_cast,static_assert,static_cast,template,typeid,typename,using,virtual,where"],G=[w,"abstract,boolean,byte,extends,final,finally,implements,import,instanceof,null,native,package,strictfp,super,synchronized,throws,transient"],
H=[G,"as,base,by,checked,decimal,delegate,descending,dynamic,event,fixed,foreach,from,group,implicit,in,interface,internal,into,is,lock,object,out,override,orderby,params,partial,readonly,ref,sbyte,sealed,stackalloc,string,select,uint,ulong,unchecked,unsafe,ushort,var"],w=[w,"debugger,eval,export,function,get,null,set,undefined,var,with,Infinity,NaN"],I=[v,"and,as,assert,class,def,del,elif,except,exec,finally,from,global,import,in,is,lambda,nonlocal,not,or,pass,print,raise,try,with,yield,False,True,None"],
J=[v,"alias,and,begin,case,class,def,defined,elsif,end,ensure,false,in,module,next,nil,not,or,redo,rescue,retry,self,super,then,true,undef,unless,until,when,yield,BEGIN,END"],v=[v,"case,done,elif,esac,eval,fi,function,in,local,set,then,until"],K=/^(DIR|FILE|vector|(de|priority_)?queue|list|stack|(const_)?iterator|(multi)?(set|map)|bitset|u?(int|float)\d*)/,N=/\S/,O=u({keywords:[F,H,w,"caller,delete,die,do,dump,elsif,eval,exit,foreach,for,goto,if,import,last,local,my,next,no,our,print,package,redo,require,sub,undef,unless,until,use,wantarray,while,BEGIN,END"+
I,J,v],hashComments:!0,cStyleComments:!0,multiLineStrings:!0,regexLiterals:!0}),A={};k(O,["default-code"]);k(x([],[["pln",/^[^<?]+/],["dec",/^<!\w[^>]*(?:>|$)/],["com",/^<\!--[\S\s]*?(?:--\>|$)/],["lang-",/^<\?([\S\s]+?)(?:\?>|$)/],["lang-",/^<%([\S\s]+?)(?:%>|$)/],["pun",/^(?:<[%?]|[%?]>)/],["lang-",/^<xmp\b[^>]*>([\S\s]+?)<\/xmp\b[^>]*>/i],["lang-js",/^<script\b[^>]*>([\S\s]*?)(<\/script\b[^>]*>)/i],["lang-css",/^<style\b[^>]*>([\S\s]*?)(<\/style\b[^>]*>)/i],["lang-in.tag",/^(<\/?[a-z][^<>]*>)/i]]),
["default-markup","htm","html","mxml","xhtml","xml","xsl"]);k(x([["pln",/^\s+/,q," \t\r\n"],["atv",/^(?:"[^"]*"?|'[^']*'?)/,q,"\"'"]],[["tag",/^^<\/?[a-z](?:[\w-.:]*\w)?|\/?>$/i],["atn",/^(?!style[\s=]|on)[a-z](?:[\w:-]*\w)?/i],["lang-uq.val",/^=\s*([^\s"'>]*(?:[^\s"'/>]|\/(?=\s)))/],["pun",/^[/<->]+/],["lang-js",/^on\w+\s*=\s*"([^"]+)"/i],["lang-js",/^on\w+\s*=\s*'([^']+)'/i],["lang-js",/^on\w+\s*=\s*([^\s"'>]+)/i],["lang-css",/^style\s*=\s*"([^"]+)"/i],["lang-css",/^style\s*=\s*'([^']+)'/i],["lang-css",
/^style\s*=\s*([^\s"'>]+)/i]]),["in.tag"]);k(x([],[["atv",/^[\S\s]+/]]),["uq.val"]);k(u({keywords:F,hashComments:!0,cStyleComments:!0,types:K}),["c","cc","cpp","cxx","cyc","m"]);k(u({keywords:"null,true,false"}),["json"]);k(u({keywords:H,hashComments:!0,cStyleComments:!0,verbatimStrings:!0,types:K}),["cs"]);k(u({keywords:G,cStyleComments:!0}),["java"]);k(u({keywords:v,hashComments:!0,multiLineStrings:!0}),["bsh","csh","sh"]);k(u({keywords:I,hashComments:!0,multiLineStrings:!0,tripleQuotedStrings:!0}),
["cv","py"]);k(u({keywords:"caller,delete,die,do,dump,elsif,eval,exit,foreach,for,goto,if,import,last,local,my,next,no,our,print,package,redo,require,sub,undef,unless,until,use,wantarray,while,BEGIN,END",hashComments:!0,multiLineStrings:!0,regexLiterals:!0}),["perl","pl","pm"]);k(u({keywords:J,hashComments:!0,multiLineStrings:!0,regexLiterals:!0}),["rb"]);k(u({keywords:w,cStyleComments:!0,regexLiterals:!0}),["js"]);k(u({keywords:"all,and,by,catch,class,else,extends,false,finally,for,if,in,is,isnt,loop,new,no,not,null,of,off,on,or,return,super,then,true,try,unless,until,when,while,yes",
hashComments:3,cStyleComments:!0,multilineStrings:!0,tripleQuotedStrings:!0,regexLiterals:!0}),["coffee"]);k(x([],[["str",/^[\S\s]+/]]),["regex"]);window.prettyPrintOne=function(a,m,e){var h=document.createElement("PRE");h.innerHTML=a;e&&D(h,e);E({g:m,i:e,h:h});return h.innerHTML};window.prettyPrint=function(a){function m(){for(var e=window.PR_SHOULD_USE_CONTINUATION?l.now()+250:Infinity;p<h.length&&l.now()<e;p++){var n=h[p],k=n.className;if(k.indexOf("prettyprint")>=0){var k=k.match(g),f,b;if(b=
!k){b=n;for(var o=void 0,c=b.firstChild;c;c=c.nextSibling)var i=c.nodeType,o=i===1?o?b:c:i===3?N.test(c.nodeValue)?b:o:o;b=(f=o===b?void 0:o)&&"CODE"===f.tagName}b&&(k=f.className.match(g));k&&(k=k[1]);b=!1;for(o=n.parentNode;o;o=o.parentNode)if((o.tagName==="pre"||o.tagName==="code"||o.tagName==="xmp")&&o.className&&o.className.indexOf("prettyprint")>=0){b=!0;break}b||((b=(b=n.className.match(/\blinenums\b(?::(\d+))?/))?b[1]&&b[1].length?+b[1]:!0:!1)&&D(n,b),d={g:k,h:n,i:b},E(d))}}p<h.length?setTimeout(m,
250):a&&a()}for(var e=[document.getElementsByTagName("pre"),document.getElementsByTagName("code"),document.getElementsByTagName("xmp")],h=[],k=0;k<e.length;++k)for(var t=0,s=e[k].length;t<s;++t)h.push(e[k][t]);var e=q,l=Date;l.now||(l={now:function(){return+new Date}});var p=0,d,g=/\blang(?:uage)?-([\w.]+)(?!\S)/;m()};window.PR={createSimpleLexer:x,registerLangHandler:k,sourceDecorator:u,PR_ATTRIB_NAME:"atn",PR_ATTRIB_VALUE:"atv",PR_COMMENT:"com",PR_DECLARATION:"dec",PR_KEYWORD:"kwd",PR_LITERAL:"lit",
PR_NOCODE:"nocode",PR_PLAIN:"pln",PR_PUNCTUATION:"pun",PR_SOURCE:"src",PR_STRING:"str",PR_TAG:"tag",PR_TYPE:"typ"}})();

;
/*!
 * jQuery JavaScript Library v1.5.2
 * http://jquery.com/
 *
 * Copyright 2011, John Resig
 * Dual licensed under the MIT or GPL Version 2 licenses.
 * http://jquery.org/license
 *
 * Includes Sizzle.js
 * http://sizzlejs.com/
 * Copyright 2011, The Dojo Foundation
 * Released under the MIT, BSD, and GPL Licenses.
 *
 * Date: Thu Mar 31 15:28:23 2011 -0400
 */
(function(a,b){function ci(a){return d.isWindow(a)?a:a.nodeType===9?a.defaultView||a.parentWindow:!1}function cf(a){if(!b_[a]){var b=d("<"+a+">").appendTo("body"),c=b.css("display");b.remove();if(c==="none"||c==="")c="block";b_[a]=c}return b_[a]}function ce(a,b){var c={};d.each(cd.concat.apply([],cd.slice(0,b)),function(){c[this]=a});return c}function b$(){try{return new a.ActiveXObject("Microsoft.XMLHTTP")}catch(b){}}function bZ(){try{return new a.XMLHttpRequest}catch(b){}}function bY(){d(a).unload(function(){for(var a in bW)bW[a](0,1)})}function bS(a,c){a.dataFilter&&(c=a.dataFilter(c,a.dataType));var e=a.dataTypes,f={},g,h,i=e.length,j,k=e[0],l,m,n,o,p;for(g=1;g<i;g++){if(g===1)for(h in a.converters)typeof h==="string"&&(f[h.toLowerCase()]=a.converters[h]);l=k,k=e[g];if(k==="*")k=l;else if(l!=="*"&&l!==k){m=l+" "+k,n=f[m]||f["* "+k];if(!n){p=b;for(o in f){j=o.split(" ");if(j[0]===l||j[0]==="*"){p=f[j[1]+" "+k];if(p){o=f[o],o===!0?n=p:p===!0&&(n=o);break}}}}!n&&!p&&d.error("No conversion from "+m.replace(" "," to ")),n!==!0&&(c=n?n(c):p(o(c)))}}return c}function bR(a,c,d){var e=a.contents,f=a.dataTypes,g=a.responseFields,h,i,j,k;for(i in g)i in d&&(c[g[i]]=d[i]);while(f[0]==="*")f.shift(),h===b&&(h=a.mimeType||c.getResponseHeader("content-type"));if(h)for(i in e)if(e[i]&&e[i].test(h)){f.unshift(i);break}if(f[0]in d)j=f[0];else{for(i in d){if(!f[0]||a.converters[i+" "+f[0]]){j=i;break}k||(k=i)}j=j||k}if(j){j!==f[0]&&f.unshift(j);return d[j]}}function bQ(a,b,c,e){if(d.isArray(b)&&b.length)d.each(b,function(b,f){c||bs.test(a)?e(a,f):bQ(a+"["+(typeof f==="object"||d.isArray(f)?b:"")+"]",f,c,e)});else if(c||b==null||typeof b!=="object")e(a,b);else if(d.isArray(b)||d.isEmptyObject(b))e(a,"");else for(var f in b)bQ(a+"["+f+"]",b[f],c,e)}function bP(a,c,d,e,f,g){f=f||c.dataTypes[0],g=g||{},g[f]=!0;var h=a[f],i=0,j=h?h.length:0,k=a===bJ,l;for(;i<j&&(k||!l);i++)l=h[i](c,d,e),typeof l==="string"&&(!k||g[l]?l=b:(c.dataTypes.unshift(l),l=bP(a,c,d,e,l,g)));(k||!l)&&!g["*"]&&(l=bP(a,c,d,e,"*",g));return l}function bO(a){return function(b,c){typeof b!=="string"&&(c=b,b="*");if(d.isFunction(c)){var e=b.toLowerCase().split(bD),f=0,g=e.length,h,i,j;for(;f<g;f++)h=e[f],j=/^\+/.test(h),j&&(h=h.substr(1)||"*"),i=a[h]=a[h]||[],i[j?"unshift":"push"](c)}}}function bq(a,b,c){var e=b==="width"?bk:bl,f=b==="width"?a.offsetWidth:a.offsetHeight;if(c==="border")return f;d.each(e,function(){c||(f-=parseFloat(d.css(a,"padding"+this))||0),c==="margin"?f+=parseFloat(d.css(a,"margin"+this))||0:f-=parseFloat(d.css(a,"border"+this+"Width"))||0});return f}function bc(a,b){b.src?d.ajax({url:b.src,async:!1,dataType:"script"}):d.globalEval(b.text||b.textContent||b.innerHTML||""),b.parentNode&&b.parentNode.removeChild(b)}function bb(a){return"getElementsByTagName"in a?a.getElementsByTagName("*"):"querySelectorAll"in a?a.querySelectorAll("*"):[]}function ba(a,b){if(b.nodeType===1){var c=b.nodeName.toLowerCase();b.clearAttributes(),b.mergeAttributes(a);if(c==="object")b.outerHTML=a.outerHTML;else if(c!=="input"||a.type!=="checkbox"&&a.type!=="radio"){if(c==="option")b.selected=a.defaultSelected;else if(c==="input"||c==="textarea")b.defaultValue=a.defaultValue}else a.checked&&(b.defaultChecked=b.checked=a.checked),b.value!==a.value&&(b.value=a.value);b.removeAttribute(d.expando)}}function _(a,b){if(b.nodeType===1&&d.hasData(a)){var c=d.expando,e=d.data(a),f=d.data(b,e);if(e=e[c]){var g=e.events;f=f[c]=d.extend({},e);if(g){delete f.handle,f.events={};for(var h in g)for(var i=0,j=g[h].length;i<j;i++)d.event.add(b,h+(g[h][i].namespace?".":"")+g[h][i].namespace,g[h][i],g[h][i].data)}}}}function $(a,b){return d.nodeName(a,"table")?a.getElementsByTagName("tbody")[0]||a.appendChild(a.ownerDocument.createElement("tbody")):a}function Q(a,b,c){if(d.isFunction(b))return d.grep(a,function(a,d){var e=!!b.call(a,d,a);return e===c});if(b.nodeType)return d.grep(a,function(a,d){return a===b===c});if(typeof b==="string"){var e=d.grep(a,function(a){return a.nodeType===1});if(L.test(b))return d.filter(b,e,!c);b=d.filter(b,e)}return d.grep(a,function(a,e){return d.inArray(a,b)>=0===c})}function P(a){return!a||!a.parentNode||a.parentNode.nodeType===11}function H(a,b){return(a&&a!=="*"?a+".":"")+b.replace(t,"`").replace(u,"&")}function G(a){var b,c,e,f,g,h,i,j,k,l,m,n,o,p=[],q=[],s=d._data(this,"events");if(a.liveFired!==this&&s&&s.live&&!a.target.disabled&&(!a.button||a.type!=="click")){a.namespace&&(n=new RegExp("(^|\\.)"+a.namespace.split(".").join("\\.(?:.*\\.)?")+"(\\.|$)")),a.liveFired=this;var t=s.live.slice(0);for(i=0;i<t.length;i++)g=t[i],g.origType.replace(r,"")===a.type?q.push(g.selector):t.splice(i--,1);f=d(a.target).closest(q,a.currentTarget);for(j=0,k=f.length;j<k;j++){m=f[j];for(i=0;i<t.length;i++){g=t[i];if(m.selector===g.selector&&(!n||n.test(g.namespace))&&!m.elem.disabled){h=m.elem,e=null;if(g.preType==="mouseenter"||g.preType==="mouseleave")a.type=g.preType,e=d(a.relatedTarget).closest(g.selector)[0];(!e||e!==h)&&p.push({elem:h,handleObj:g,level:m.level})}}}for(j=0,k=p.length;j<k;j++){f=p[j];if(c&&f.level>c)break;a.currentTarget=f.elem,a.data=f.handleObj.data,a.handleObj=f.handleObj,o=f.handleObj.origHandler.apply(f.elem,arguments);if(o===!1||a.isPropagationStopped()){c=f.level,o===!1&&(b=!1);if(a.isImmediatePropagationStopped())break}}return b}}function E(a,c,e){var f=d.extend({},e[0]);f.type=a,f.originalEvent={},f.liveFired=b,d.event.handle.call(c,f),f.isDefaultPrevented()&&e[0].preventDefault()}function y(){return!0}function x(){return!1}function i(a){for(var b in a)if(b!=="toJSON")return!1;return!0}function h(a,c,e){if(e===b&&a.nodeType===1){e=a.getAttribute("data-"+c);if(typeof e==="string"){try{e=e==="true"?!0:e==="false"?!1:e==="null"?null:d.isNaN(e)?g.test(e)?d.parseJSON(e):e:parseFloat(e)}catch(f){}d.data(a,c,e)}else e=b}return e}var c=a.document,d=function(){function G(){if(!d.isReady){try{c.documentElement.doScroll("left")}catch(a){setTimeout(G,1);return}d.ready()}}var d=function(a,b){return new d.fn.init(a,b,g)},e=a.jQuery,f=a.$,g,h=/^(?:[^<]*(<[\w\W]+>)[^>]*$|#([\w\-]+)$)/,i=/\S/,j=/^\s+/,k=/\s+$/,l=/\d/,m=/^<(\w+)\s*\/?>(?:<\/\1>)?$/,n=/^[\],:{}\s]*$/,o=/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g,p=/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g,q=/(?:^|:|,)(?:\s*\[)+/g,r=/(webkit)[ \/]([\w.]+)/,s=/(opera)(?:.*version)?[ \/]([\w.]+)/,t=/(msie) ([\w.]+)/,u=/(mozilla)(?:.*? rv:([\w.]+))?/,v=navigator.userAgent,w,x,y,z=Object.prototype.toString,A=Object.prototype.hasOwnProperty,B=Array.prototype.push,C=Array.prototype.slice,D=String.prototype.trim,E=Array.prototype.indexOf,F={};d.fn=d.prototype={constructor:d,init:function(a,e,f){var g,i,j,k;if(!a)return this;if(a.nodeType){this.context=this[0]=a,this.length=1;return this}if(a==="body"&&!e&&c.body){this.context=c,this[0]=c.body,this.selector="body",this.length=1;return this}if(typeof a==="string"){g=h.exec(a);if(!g||!g[1]&&e)return!e||e.jquery?(e||f).find(a):this.constructor(e).find(a);if(g[1]){e=e instanceof d?e[0]:e,k=e?e.ownerDocument||e:c,j=m.exec(a),j?d.isPlainObject(e)?(a=[c.createElement(j[1])],d.fn.attr.call(a,e,!0)):a=[k.createElement(j[1])]:(j=d.buildFragment([g[1]],[k]),a=(j.cacheable?d.clone(j.fragment):j.fragment).childNodes);return d.merge(this,a)}i=c.getElementById(g[2]);if(i&&i.parentNode){if(i.id!==g[2])return f.find(a);this.length=1,this[0]=i}this.context=c,this.selector=a;return this}if(d.isFunction(a))return f.ready(a);a.selector!==b&&(this.selector=a.selector,this.context=a.context);return d.makeArray(a,this)},selector:"",jquery:"1.5.2",length:0,size:function(){return this.length},toArray:function(){return C.call(this,0)},get:function(a){return a==null?this.toArray():a<0?this[this.length+a]:this[a]},pushStack:function(a,b,c){var e=this.constructor();d.isArray(a)?B.apply(e,a):d.merge(e,a),e.prevObject=this,e.context=this.context,b==="find"?e.selector=this.selector+(this.selector?" ":"")+c:b&&(e.selector=this.selector+"."+b+"("+c+")");return e},each:function(a,b){return d.each(this,a,b)},ready:function(a){d.bindReady(),x.done(a);return this},eq:function(a){return a===-1?this.slice(a):this.slice(a,+a+1)},first:function(){return this.eq(0)},last:function(){return this.eq(-1)},slice:function(){return this.pushStack(C.apply(this,arguments),"slice",C.call(arguments).join(","))},map:function(a){return this.pushStack(d.map(this,function(b,c){return a.call(b,c,b)}))},end:function(){return this.prevObject||this.constructor(null)},push:B,sort:[].sort,splice:[].splice},d.fn.init.prototype=d.fn,d.extend=d.fn.extend=function(){var a,c,e,f,g,h,i=arguments[0]||{},j=1,k=arguments.length,l=!1;typeof i==="boolean"&&(l=i,i=arguments[1]||{},j=2),typeof i!=="object"&&!d.isFunction(i)&&(i={}),k===j&&(i=this,--j);for(;j<k;j++)if((a=arguments[j])!=null)for(c in a){e=i[c],f=a[c];if(i===f)continue;l&&f&&(d.isPlainObject(f)||(g=d.isArray(f)))?(g?(g=!1,h=e&&d.isArray(e)?e:[]):h=e&&d.isPlainObject(e)?e:{},i[c]=d.extend(l,h,f)):f!==b&&(i[c]=f)}return i},d.extend({noConflict:function(b){a.$=f,b&&(a.jQuery=e);return d},isReady:!1,readyWait:1,ready:function(a){a===!0&&d.readyWait--;if(!d.readyWait||a!==!0&&!d.isReady){if(!c.body)return setTimeout(d.ready,1);d.isReady=!0;if(a!==!0&&--d.readyWait>0)return;x.resolveWith(c,[d]),d.fn.trigger&&d(c).trigger("ready").unbind("ready")}},bindReady:function(){if(!x){x=d._Deferred();if(c.readyState==="complete")return setTimeout(d.ready,1);if(c.addEventListener)c.addEventListener("DOMContentLoaded",y,!1),a.addEventListener("load",d.ready,!1);else if(c.attachEvent){c.attachEvent("onreadystatechange",y),a.attachEvent("onload",d.ready);var b=!1;try{b=a.frameElement==null}catch(e){}c.documentElement.doScroll&&b&&G()}}},isFunction:function(a){return d.type(a)==="function"},isArray:Array.isArray||function(a){return d.type(a)==="array"},isWindow:function(a){return a&&typeof a==="object"&&"setInterval"in a},isNaN:function(a){return a==null||!l.test(a)||isNaN(a)},type:function(a){return a==null?String(a):F[z.call(a)]||"object"},isPlainObject:function(a){if(!a||d.type(a)!=="object"||a.nodeType||d.isWindow(a))return!1;if(a.constructor&&!A.call(a,"constructor")&&!A.call(a.constructor.prototype,"isPrototypeOf"))return!1;var c;for(c in a){}return c===b||A.call(a,c)},isEmptyObject:function(a){for(var b in a)return!1;return!0},error:function(a){throw a},parseJSON:function(b){if(typeof b!=="string"||!b)return null;b=d.trim(b);if(n.test(b.replace(o,"@").replace(p,"]").replace(q,"")))return a.JSON&&a.JSON.parse?a.JSON.parse(b):(new Function("return "+b))();d.error("Invalid JSON: "+b)},parseXML:function(b,c,e){a.DOMParser?(e=new DOMParser,c=e.parseFromString(b,"text/xml")):(c=new ActiveXObject("Microsoft.XMLDOM"),c.async="false",c.loadXML(b)),e=c.documentElement,(!e||!e.nodeName||e.nodeName==="parsererror")&&d.error("Invalid XML: "+b);return c},noop:function(){},globalEval:function(a){if(a&&i.test(a)){var b=c.head||c.getElementsByTagName("head")[0]||c.documentElement,e=c.createElement("script");d.support.scriptEval()?e.appendChild(c.createTextNode(a)):e.text=a,b.insertBefore(e,b.firstChild),b.removeChild(e)}},nodeName:function(a,b){return a.nodeName&&a.nodeName.toUpperCase()===b.toUpperCase()},each:function(a,c,e){var f,g=0,h=a.length,i=h===b||d.isFunction(a);if(e){if(i){for(f in a)if(c.apply(a[f],e)===!1)break}else for(;g<h;)if(c.apply(a[g++],e)===!1)break}else if(i){for(f in a)if(c.call(a[f],f,a[f])===!1)break}else for(var j=a[0];g<h&&c.call(j,g,j)!==!1;j=a[++g]){}return a},trim:D?function(a){return a==null?"":D.call(a)}:function(a){return a==null?"":(a+"").replace(j,"").replace(k,"")},makeArray:function(a,b){var c=b||[];if(a!=null){var e=d.type(a);a.length==null||e==="string"||e==="function"||e==="regexp"||d.isWindow(a)?B.call(c,a):d.merge(c,a)}return c},inArray:function(a,b){if(b.indexOf)return b.indexOf(a);for(var c=0,d=b.length;c<d;c++)if(b[c]===a)return c;return-1},merge:function(a,c){var d=a.length,e=0;if(typeof c.length==="number")for(var f=c.length;e<f;e++)a[d++]=c[e];else while(c[e]!==b)a[d++]=c[e++];a.length=d;return a},grep:function(a,b,c){var d=[],e;c=!!c;for(var f=0,g=a.length;f<g;f++)e=!!b(a[f],f),c!==e&&d.push(a[f]);return d},map:function(a,b,c){var d=[],e;for(var f=0,g=a.length;f<g;f++)e=b(a[f],f,c),e!=null&&(d[d.length]=e);return d.concat.apply([],d)},guid:1,proxy:function(a,c,e){arguments.length===2&&(typeof c==="string"?(e=a,a=e[c],c=b):c&&!d.isFunction(c)&&(e=c,c=b)),!c&&a&&(c=function(){return a.apply(e||this,arguments)}),a&&(c.guid=a.guid=a.guid||c.guid||d.guid++);return c},access:function(a,c,e,f,g,h){var i=a.length;if(typeof c==="object"){for(var j in c)d.access(a,j,c[j],f,g,e);return a}if(e!==b){f=!h&&f&&d.isFunction(e);for(var k=0;k<i;k++)g(a[k],c,f?e.call(a[k],k,g(a[k],c)):e,h);return a}return i?g(a[0],c):b},now:function(){return(new Date).getTime()},uaMatch:function(a){a=a.toLowerCase();var b=r.exec(a)||s.exec(a)||t.exec(a)||a.indexOf("compatible")<0&&u.exec(a)||[];return{browser:b[1]||"",version:b[2]||"0"}},sub:function(){function a(b,c){return new a.fn.init(b,c)}d.extend(!0,a,this),a.superclass=this,a.fn=a.prototype=this(),a.fn.constructor=a,a.subclass=this.subclass,a.fn.init=function b(b,c){c&&c instanceof d&&!(c instanceof a)&&(c=a(c));return d.fn.init.call(this,b,c,e)},a.fn.init.prototype=a.fn;var e=a(c);return a},browser:{}}),d.each("Boolean Number String Function Array Date RegExp Object".split(" "),function(a,b){F["[object "+b+"]"]=b.toLowerCase()}),w=d.uaMatch(v),w.browser&&(d.browser[w.browser]=!0,d.browser.version=w.version),d.browser.webkit&&(d.browser.safari=!0),E&&(d.inArray=function(a,b){return E.call(b,a)}),i.test(" ")&&(j=/^[\s\xA0]+/,k=/[\s\xA0]+$/),g=d(c),c.addEventListener?y=function(){c.removeEventListener("DOMContentLoaded",y,!1),d.ready()}:c.attachEvent&&(y=function(){c.readyState==="complete"&&(c.detachEvent("onreadystatechange",y),d.ready())});return d}(),e="then done fail isResolved isRejected promise".split(" "),f=[].slice;d.extend({_Deferred:function(){var a=[],b,c,e,f={done:function(){if(!e){var c=arguments,g,h,i,j,k;b&&(k=b,b=0);for(g=0,h=c.length;g<h;g++)i=c[g],j=d.type(i),j==="array"?f.done.apply(f,i):j==="function"&&a.push(i);k&&f.resolveWith(k[0],k[1])}return this},resolveWith:function(d,f){if(!e&&!b&&!c){f=f||[],c=1;try{while(a[0])a.shift().apply(d,f)}finally{b=[d,f],c=0}}return this},resolve:function(){f.resolveWith(this,arguments);return this},isResolved:function(){return c||b},cancel:function(){e=1,a=[];return this}};return f},Deferred:function(a){var b=d._Deferred(),c=d._Deferred(),f;d.extend(b,{then:function(a,c){b.done(a).fail(c);return this},fail:c.done,rejectWith:c.resolveWith,reject:c.resolve,isRejected:c.isResolved,promise:function(a){if(a==null){if(f)return f;f=a={}}var c=e.length;while(c--)a[e[c]]=b[e[c]];return a}}),b.done(c.cancel).fail(b.cancel),delete b.cancel,a&&a.call(b,b);return b},when:function(a){function i(a){return function(c){b[a]=arguments.length>1?f.call(arguments,0):c,--g||h.resolveWith(h,f.call(b,0))}}var b=arguments,c=0,e=b.length,g=e,h=e<=1&&a&&d.isFunction(a.promise)?a:d.Deferred();if(e>1){for(;c<e;c++)b[c]&&d.isFunction(b[c].promise)?b[c].promise().then(i(c),h.reject):--g;g||h.resolveWith(h,b)}else h!==a&&h.resolveWith(h,e?[a]:[]);return h.promise()}}),function(){d.support={};var b=c.createElement("div");b.style.display="none",b.innerHTML="   <link/><table></table><a href='/a' style='color:red;float:left;opacity:.55;'>a</a><input type='checkbox'/>";var e=b.getElementsByTagName("*"),f=b.getElementsByTagName("a")[0],g=c.createElement("select"),h=g.appendChild(c.createElement("option")),i=b.getElementsByTagName("input")[0];if(e&&e.length&&f){d.support={leadingWhitespace:b.firstChild.nodeType===3,tbody:!b.getElementsByTagName("tbody").length,htmlSerialize:!!b.getElementsByTagName("link").length,style:/red/.test(f.getAttribute("style")),hrefNormalized:f.getAttribute("href")==="/a",opacity:/^0.55$/.test(f.style.opacity),cssFloat:!!f.style.cssFloat,checkOn:i.value==="on",optSelected:h.selected,deleteExpando:!0,optDisabled:!1,checkClone:!1,noCloneEvent:!0,noCloneChecked:!0,boxModel:null,inlineBlockNeedsLayout:!1,shrinkWrapBlocks:!1,reliableHiddenOffsets:!0,reliableMarginRight:!0},i.checked=!0,d.support.noCloneChecked=i.cloneNode(!0).checked,g.disabled=!0,d.support.optDisabled=!h.disabled;var j=null;d.support.scriptEval=function(){if(j===null){var b=c.documentElement,e=c.createElement("script"),f="script"+d.now();try{e.appendChild(c.createTextNode("window."+f+"=1;"))}catch(g){}b.insertBefore(e,b.firstChild),a[f]?(j=!0,delete a[f]):j=!1,b.removeChild(e)}return j};try{delete b.test}catch(k){d.support.deleteExpando=!1}!b.addEventListener&&b.attachEvent&&b.fireEvent&&(b.attachEvent("onclick",function l(){d.support.noCloneEvent=!1,b.detachEvent("onclick",l)}),b.cloneNode(!0).fireEvent("onclick")),b=c.createElement("div"),b.innerHTML="<input type='radio' name='radiotest' checked='checked'/>";var m=c.createDocumentFragment();m.appendChild(b.firstChild),d.support.checkClone=m.cloneNode(!0).cloneNode(!0).lastChild.checked,d(function(){var a=c.createElement("div"),b=c.getElementsByTagName("body")[0];if(b){a.style.width=a.style.paddingLeft="1px",b.appendChild(a),d.boxModel=d.support.boxModel=a.offsetWidth===2,"zoom"in a.style&&(a.style.display="inline",a.style.zoom=1,d.support.inlineBlockNeedsLayout=a.offsetWidth===2,a.style.display="",a.innerHTML="<div style='width:4px;'></div>",d.support.shrinkWrapBlocks=a.offsetWidth!==2),a.innerHTML="<table><tr><td style='padding:0;border:0;display:none'></td><td>t</td></tr></table>";var e=a.getElementsByTagName("td");d.support.reliableHiddenOffsets=e[0].offsetHeight===0,e[0].style.display="",e[1].style.display="none",d.support.reliableHiddenOffsets=d.support.reliableHiddenOffsets&&e[0].offsetHeight===0,a.innerHTML="",c.defaultView&&c.defaultView.getComputedStyle&&(a.style.width="1px",a.style.marginRight="0",d.support.reliableMarginRight=(parseInt(c.defaultView.getComputedStyle(a,null).marginRight,10)||0)===0),b.removeChild(a).style.display="none",a=e=null}});var n=function(a){var b=c.createElement("div");a="on"+a;if(!b.attachEvent)return!0;var d=a in b;d||(b.setAttribute(a,"return;"),d=typeof b[a]==="function");return d};d.support.submitBubbles=n("submit"),d.support.changeBubbles=n("change"),b=e=f=null}}();var g=/^(?:\{.*\}|\[.*\])$/;d.extend({cache:{},uuid:0,expando:"jQuery"+(d.fn.jquery+Math.random()).replace(/\D/g,""),noData:{embed:!0,object:"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000",applet:!0},hasData:function(a){a=a.nodeType?d.cache[a[d.expando]]:a[d.expando];return!!a&&!i(a)},data:function(a,c,e,f){if(d.acceptData(a)){var g=d.expando,h=typeof c==="string",i,j=a.nodeType,k=j?d.cache:a,l=j?a[d.expando]:a[d.expando]&&d.expando;if((!l||f&&l&&!k[l][g])&&h&&e===b)return;l||(j?a[d.expando]=l=++d.uuid:l=d.expando),k[l]||(k[l]={},j||(k[l].toJSON=d.noop));if(typeof c==="object"||typeof c==="function")f?k[l][g]=d.extend(k[l][g],c):k[l]=d.extend(k[l],c);i=k[l],f&&(i[g]||(i[g]={}),i=i[g]),e!==b&&(i[c]=e);if(c==="events"&&!i[c])return i[g]&&i[g].events;return h?i[c]:i}},removeData:function(b,c,e){if(d.acceptData(b)){var f=d.expando,g=b.nodeType,h=g?d.cache:b,j=g?b[d.expando]:d.expando;if(!h[j])return;if(c){var k=e?h[j][f]:h[j];if(k){delete k[c];if(!i(k))return}}if(e){delete h[j][f];if(!i(h[j]))return}var l=h[j][f];d.support.deleteExpando||h!=a?delete h[j]:h[j]=null,l?(h[j]={},g||(h[j].toJSON=d.noop),h[j][f]=l):g&&(d.support.deleteExpando?delete b[d.expando]:b.removeAttribute?b.removeAttribute(d.expando):b[d.expando]=null)}},_data:function(a,b,c){return d.data(a,b,c,!0)},acceptData:function(a){if(a.nodeName){var b=d.noData[a.nodeName.toLowerCase()];if(b)return b!==!0&&a.getAttribute("classid")===b}return!0}}),d.fn.extend({data:function(a,c){var e=null;if(typeof a==="undefined"){if(this.length){e=d.data(this[0]);if(this[0].nodeType===1){var f=this[0].attributes,g;for(var i=0,j=f.length;i<j;i++)g=f[i].name,g.indexOf("data-")===0&&(g=g.substr(5),h(this[0],g,e[g]))}}return e}if(typeof a==="object")return this.each(function(){d.data(this,a)});var k=a.split(".");k[1]=k[1]?"."+k[1]:"";if(c===b){e=this.triggerHandler("getData"+k[1]+"!",[k[0]]),e===b&&this.length&&(e=d.data(this[0],a),e=h(this[0],a,e));return e===b&&k[1]?this.data(k[0]):e}return this.each(function(){var b=d(this),e=[k[0],c];b.triggerHandler("setData"+k[1]+"!",e),d.data(this,a,c),b.triggerHandler("changeData"+k[1]+"!",e)})},removeData:function(a){return this.each(function(){d.removeData(this,a)})}}),d.extend({queue:function(a,b,c){if(a){b=(b||"fx")+"queue";var e=d._data(a,b);if(!c)return e||[];!e||d.isArray(c)?e=d._data(a,b,d.makeArray(c)):e.push(c);return e}},dequeue:function(a,b){b=b||"fx";var c=d.queue(a,b),e=c.shift();e==="inprogress"&&(e=c.shift()),e&&(b==="fx"&&c.unshift("inprogress"),e.call(a,function(){d.dequeue(a,b)})),c.length||d.removeData(a,b+"queue",!0)}}),d.fn.extend({queue:function(a,c){typeof a!=="string"&&(c=a,a="fx");if(c===b)return d.queue(this[0],a);return this.each(function(b){var e=d.queue(this,a,c);a==="fx"&&e[0]!=="inprogress"&&d.dequeue(this,a)})},dequeue:function(a){return this.each(function(){d.dequeue(this,a)})},delay:function(a,b){a=d.fx?d.fx.speeds[a]||a:a,b=b||"fx";return this.queue(b,function(){var c=this;setTimeout(function(){d.dequeue(c,b)},a)})},clearQueue:function(a){return this.queue(a||"fx",[])}});var j=/[\n\t\r]/g,k=/\s+/,l=/\r/g,m=/^(?:href|src|style)$/,n=/^(?:button|input)$/i,o=/^(?:button|input|object|select|textarea)$/i,p=/^a(?:rea)?$/i,q=/^(?:radio|checkbox)$/i;d.props={"for":"htmlFor","class":"className",readonly:"readOnly",maxlength:"maxLength",cellspacing:"cellSpacing",rowspan:"rowSpan",colspan:"colSpan",tabindex:"tabIndex",usemap:"useMap",frameborder:"frameBorder"},d.fn.extend({attr:function(a,b){return d.access(this,a,b,!0,d.attr)},removeAttr:function(a,b){return this.each(function(){d.attr(this,a,""),this.nodeType===1&&this.removeAttribute(a)})},addClass:function(a){if(d.isFunction(a))return this.each(function(b){var c=d(this);c.addClass(a.call(this,b,c.attr("class")))});if(a&&typeof a==="string"){var b=(a||"").split(k);for(var c=0,e=this.length;c<e;c++){var f=this[c];if(f.nodeType===1)if(f.className){var g=" "+f.className+" ",h=f.className;for(var i=0,j=b.length;i<j;i++)g.indexOf(" "+b[i]+" ")<0&&(h+=" "+b[i]);f.className=d.trim(h)}else f.className=a}}return this},removeClass:function(a){if(d.isFunction(a))return this.each(function(b){var c=d(this);c.removeClass(a.call(this,b,c.attr("class")))});if(a&&typeof a==="string"||a===b){var c=(a||"").split(k);for(var e=0,f=this.length;e<f;e++){var g=this[e];if(g.nodeType===1&&g.className)if(a){var h=(" "+g.className+" ").replace(j," ");for(var i=0,l=c.length;i<l;i++)h=h.replace(" "+c[i]+" "," ");g.className=d.trim(h)}else g.className=""}}return this},toggleClass:function(a,b){var c=typeof a,e=typeof b==="boolean";if(d.isFunction(a))return this.each(function(c){var e=d(this);e.toggleClass(a.call(this,c,e.attr("class"),b),b)});return this.each(function(){if(c==="string"){var f,g=0,h=d(this),i=b,j=a.split(k);while(f=j[g++])i=e?i:!h.hasClass(f),h[i?"addClass":"removeClass"](f)}else if(c==="undefined"||c==="boolean")this.className&&d._data(this,"__className__",this.className),this.className=this.className||a===!1?"":d._data(this,"__className__")||""})},hasClass:function(a){var b=" "+a+" ";for(var c=0,d=this.length;c<d;c++)if((" "+this[c].className+" ").replace(j," ").indexOf(b)>-1)return!0;return!1},val:function(a){if(!arguments.length){var c=this[0];if(c){if(d.nodeName(c,"option")){var e=c.attributes.value;return!e||e.specified?c.value:c.text}if(d.nodeName(c,"select")){var f=c.selectedIndex,g=[],h=c.options,i=c.type==="select-one";if(f<0)return null;for(var j=i?f:0,k=i?f+1:h.length;j<k;j++){var m=h[j];if(m.selected&&(d.support.optDisabled?!m.disabled:m.getAttribute("disabled")===null)&&(!m.parentNode.disabled||!d.nodeName(m.parentNode,"optgroup"))){a=d(m).val();if(i)return a;g.push(a)}}if(i&&!g.length&&h.length)return d(h[f]).val();return g}if(q.test(c.type)&&!d.support.checkOn)return c.getAttribute("value")===null?"on":c.value;return(c.value||"").replace(l,"")}return b}var n=d.isFunction(a);return this.each(function(b){var c=d(this),e=a;if(this.nodeType===1){n&&(e=a.call(this,b,c.val())),e==null?e="":typeof e==="number"?e+="":d.isArray(e)&&(e=d.map(e,function(a){return a==null?"":a+""}));if(d.isArray(e)&&q.test(this.type))this.checked=d.inArray(c.val(),e)>=0;else if(d.nodeName(this,"select")){var f=d.makeArray(e);d("option",this).each(function(){this.selected=d.inArray(d(this).val(),f)>=0}),f.length||(this.selectedIndex=-1)}else this.value=e}})}}),d.extend({attrFn:{val:!0,css:!0,html:!0,text:!0,data:!0,width:!0,height:!0,offset:!0},attr:function(a,c,e,f){if(!a||a.nodeType===3||a.nodeType===8||a.nodeType===2)return b;if(f&&c in d.attrFn)return d(a)[c](e);var g=a.nodeType!==1||!d.isXMLDoc(a),h=e!==b;c=g&&d.props[c]||c;if(a.nodeType===1){var i=m.test(c);if(c==="selected"&&!d.support.optSelected){var j=a.parentNode;j&&(j.selectedIndex,j.parentNode&&j.parentNode.selectedIndex)}if((c in a||a[c]!==b)&&g&&!i){h&&(c==="type"&&n.test(a.nodeName)&&a.parentNode&&d.error("type property can't be changed"),e===null?a.nodeType===1&&a.removeAttribute(c):a[c]=e);if(d.nodeName(a,"form")&&a.getAttributeNode(c))return a.getAttributeNode(c).nodeValue;if(c==="tabIndex"){var k=a.getAttributeNode("tabIndex");return k&&k.specified?k.value:o.test(a.nodeName)||p.test(a.nodeName)&&a.href?0:b}return a[c]}if(!d.support.style&&g&&c==="style"){h&&(a.style.cssText=""+e);return a.style.cssText}h&&a.setAttribute(c,""+e);if(!a.attributes[c]&&(a.hasAttribute&&!a.hasAttribute(c)))return b;var l=!d.support.hrefNormalized&&g&&i?a.getAttribute(c,2):a.getAttribute(c);return l===null?b:l}h&&(a[c]=e);return a[c]}});var r=/\.(.*)$/,s=/^(?:textarea|input|select)$/i,t=/\./g,u=/ /g,v=/[^\w\s.|`]/g,w=function(a){return a.replace(v,"\\$&")};d.event={add:function(c,e,f,g){if(c.nodeType!==3&&c.nodeType!==8){try{d.isWindow(c)&&(c!==a&&!c.frameElement)&&(c=a)}catch(h){}if(f===!1)f=x;else if(!f)return;var i,j;f.handler&&(i=f,f=i.handler),f.guid||(f.guid=d.guid++);var k=d._data(c);if(!k)return;var l=k.events,m=k.handle;l||(k.events=l={}),m||(k.handle=m=function(a){return typeof d!=="undefined"&&d.event.triggered!==a.type?d.event.handle.apply(m.elem,arguments):b}),m.elem=c,e=e.split(" ");var n,o=0,p;while(n=e[o++]){j=i?d.extend({},i):{handler:f,data:g},n.indexOf(".")>-1?(p=n.split("."),n=p.shift(),j.namespace=p.slice(0).sort().join(".")):(p=[],j.namespace=""),j.type=n,j.guid||(j.guid=f.guid);var q=l[n],r=d.event.special[n]||{};if(!q){q=l[n]=[];if(!r.setup||r.setup.call(c,g,p,m)===!1)c.addEventListener?c.addEventListener(n,m,!1):c.attachEvent&&c.attachEvent("on"+n,m)}r.add&&(r.add.call(c,j),j.handler.guid||(j.handler.guid=f.guid)),q.push(j),d.event.global[n]=!0}c=null}},global:{},remove:function(a,c,e,f){if(a.nodeType!==3&&a.nodeType!==8){e===!1&&(e=x);var g,h,i,j,k=0,l,m,n,o,p,q,r,s=d.hasData(a)&&d._data(a),t=s&&s.events;if(!s||!t)return;c&&c.type&&(e=c.handler,c=c.type);if(!c||typeof c==="string"&&c.charAt(0)==="."){c=c||"";for(h in t)d.event.remove(a,h+c);return}c=c.split(" ");while(h=c[k++]){r=h,q=null,l=h.indexOf(".")<0,m=[],l||(m=h.split("."),h=m.shift(),n=new RegExp("(^|\\.)"+d.map(m.slice(0).sort(),w).join("\\.(?:.*\\.)?")+"(\\.|$)")),p=t[h];if(!p)continue;if(!e){for(j=0;j<p.length;j++){q=p[j];if(l||n.test(q.namespace))d.event.remove(a,r,q.handler,j),p.splice(j--,1)}continue}o=d.event.special[h]||{};for(j=f||0;j<p.length;j++){q=p[j];if(e.guid===q.guid){if(l||n.test(q.namespace))f==null&&p.splice(j--,1),o.remove&&o.remove.call(a,q);if(f!=null)break}}if(p.length===0||f!=null&&p.length===1)(!o.teardown||o.teardown.call(a,m)===!1)&&d.removeEvent(a,h,s.handle),g=null,delete t[h]}if(d.isEmptyObject(t)){var u=s.handle;u&&(u.elem=null),delete s.events,delete s.handle,d.isEmptyObject(s)&&d.removeData(a,b,!0)}}},trigger:function(a,c,e){var f=a.type||a,g=arguments[3];if(!g){a=typeof a==="object"?a[d.expando]?a:d.extend(d.Event(f),a):d.Event(f),f.indexOf("!")>=0&&(a.type=f=f.slice(0,-1),a.exclusive=!0),e||(a.stopPropagation(),d.event.global[f]&&d.each(d.cache,function(){var b=d.expando,e=this[b];e&&e.events&&e.events[f]&&d.event.trigger(a,c,e.handle.elem)}));if(!e||e.nodeType===3||e.nodeType===8)return b;a.result=b,a.target=e,c=d.makeArray(c),c.unshift(a)}a.currentTarget=e;var h=d._data(e,"handle");h&&h.apply(e,c);var i=e.parentNode||e.ownerDocument;try{e&&e.nodeName&&d.noData[e.nodeName.toLowerCase()]||e["on"+f]&&e["on"+f].apply(e,c)===!1&&(a.result=!1,a.preventDefault())}catch(j){}if(!a.isPropagationStopped()&&i)d.event.trigger(a,c,i,!0);else if(!a.isDefaultPrevented()){var k,l=a.target,m=f.replace(r,""),n=d.nodeName(l,"a")&&m==="click",o=d.event.special[m]||{};if((!o._default||o._default.call(e,a)===!1)&&!n&&!(l&&l.nodeName&&d.noData[l.nodeName.toLowerCase()])){try{l[m]&&(k=l["on"+m],k&&(l["on"+m]=null),d.event.triggered=a.type,l[m]())}catch(p){}k&&(l["on"+m]=k),d.event.triggered=b}}},handle:function(c){var e,f,g,h,i,j=[],k=d.makeArray(arguments);c=k[0]=d.event.fix(c||a.event),c.currentTarget=this,e=c.type.indexOf(".")<0&&!c.exclusive,e||(g=c.type.split("."),c.type=g.shift(),j=g.slice(0).sort(),h=new RegExp("(^|\\.)"+j.join("\\.(?:.*\\.)?")+"(\\.|$)")),c.namespace=c.namespace||j.join("."),i=d._data(this,"events"),f=(i||{})[c.type];if(i&&f){f=f.slice(0);for(var l=0,m=f.length;l<m;l++){var n=f[l];if(e||h.test(n.namespace)){c.handler=n.handler,c.data=n.data,c.handleObj=n;var o=n.handler.apply(this,k);o!==b&&(c.result=o,o===!1&&(c.preventDefault(),c.stopPropagation()));if(c.isImmediatePropagationStopped())break}}}return c.result},props:"altKey attrChange attrName bubbles button cancelable charCode clientX clientY ctrlKey currentTarget data detail eventPhase fromElement handler keyCode layerX layerY metaKey newValue offsetX offsetY pageX pageY prevValue relatedNode relatedTarget screenX screenY shiftKey srcElement target toElement view wheelDelta which".split(" "),fix:function(a){if(a[d.expando])return a;var e=a;a=d.Event(e);for(var f=this.props.length,g;f;)g=this.props[--f],a[g]=e[g];a.target||(a.target=a.srcElement||c),a.target.nodeType===3&&(a.target=a.target.parentNode),!a.relatedTarget&&a.fromElement&&(a.relatedTarget=a.fromElement===a.target?a.toElement:a.fromElement);if(a.pageX==null&&a.clientX!=null){var h=c.documentElement,i=c.body;a.pageX=a.clientX+(h&&h.scrollLeft||i&&i.scrollLeft||0)-(h&&h.clientLeft||i&&i.clientLeft||0),a.pageY=a.clientY+(h&&h.scrollTop||i&&i.scrollTop||0)-(h&&h.clientTop||i&&i.clientTop||0)}a.which==null&&(a.charCode!=null||a.keyCode!=null)&&(a.which=a.charCode!=null?a.charCode:a.keyCode),!a.metaKey&&a.ctrlKey&&(a.metaKey=a.ctrlKey),!a.which&&a.button!==b&&(a.which=a.button&1?1:a.button&2?3:a.button&4?2:0);return a},guid:1e8,proxy:d.proxy,special:{ready:{setup:d.bindReady,teardown:d.noop},live:{add:function(a){d.event.add(this,H(a.origType,a.selector),d.extend({},a,{handler:G,guid:a.handler.guid}))},remove:function(a){d.event.remove(this,H(a.origType,a.selector),a)}},beforeunload:{setup:function(a,b,c){d.isWindow(this)&&(this.onbeforeunload=c)},teardown:function(a,b){this.onbeforeunload===b&&(this.onbeforeunload=null)}}}},d.removeEvent=c.removeEventListener?function(a,b,c){a.removeEventListener&&a.removeEventListener(b,c,!1)}:function(a,b,c){a.detachEvent&&a.detachEvent("on"+b,c)},d.Event=function(a){if(!this.preventDefault)return new d.Event(a);a&&a.type?(this.originalEvent=a,this.type=a.type,this.isDefaultPrevented=a.defaultPrevented||a.returnValue===!1||a.getPreventDefault&&a.getPreventDefault()?y:x):this.type=a,this.timeStamp=d.now(),this[d.expando]=!0},d.Event.prototype={preventDefault:function(){this.isDefaultPrevented=y;var a=this.originalEvent;a&&(a.preventDefault?a.preventDefault():a.returnValue=!1)},stopPropagation:function(){this.isPropagationStopped=y;var a=this.originalEvent;a&&(a.stopPropagation&&a.stopPropagation(),a.cancelBubble=!0)},stopImmediatePropagation:function(){this.isImmediatePropagationStopped=y,this.stopPropagation()},isDefaultPrevented:x,isPropagationStopped:x,isImmediatePropagationStopped:x};var z=function(a){var b=a.relatedTarget;try{if(b&&b!==c&&!b.parentNode)return;while(b&&b!==this)b=b.parentNode;b!==this&&(a.type=a.data,d.event.handle.apply(this,arguments))}catch(e){}},A=function(a){a.type=a.data,d.event.handle.apply(this,arguments)};d.each({mouseenter:"mouseover",mouseleave:"mouseout"},function(a,b){d.event.special[a]={setup:function(c){d.event.add(this,b,c&&c.selector?A:z,a)},teardown:function(a){d.event.remove(this,b,a&&a.selector?A:z)}}}),d.support.submitBubbles||(d.event.special.submit={setup:function(a,b){if(this.nodeName&&this.nodeName.toLowerCase()!=="form")d.event.add(this,"click.specialSubmit",function(a){var b=a.target,c=b.type;(c==="submit"||c==="image")&&d(b).closest("form").length&&E("submit",this,arguments)}),d.event.add(this,"keypress.specialSubmit",function(a){var b=a.target,c=b.type;(c==="text"||c==="password")&&d(b).closest("form").length&&a.keyCode===13&&E("submit",this,arguments)});else return!1},teardown:function(a){d.event.remove(this,".specialSubmit")}});if(!d.support.changeBubbles){var B,C=function(a){var b=a.type,c=a.value;b==="radio"||b==="checkbox"?c=a.checked:b==="select-multiple"?c=a.selectedIndex>-1?d.map(a.options,function(a){return a.selected}).join("-"):"":a.nodeName.toLowerCase()==="select"&&(c=a.selectedIndex);return c},D=function D(a){var c=a.target,e,f;if(s.test(c.nodeName)&&!c.readOnly){e=d._data(c,"_change_data"),f=C(c),(a.type!=="focusout"||c.type!=="radio")&&d._data(c,"_change_data",f);if(e===b||f===e)return;if(e!=null||f)a.type="change",a.liveFired=b,d.event.trigger(a,arguments[1],c)}};d.event.special.change={filters:{focusout:D,beforedeactivate:D,click:function(a){var b=a.target,c=b.type;(c==="radio"||c==="checkbox"||b.nodeName.toLowerCase()==="select")&&D.call(this,a)},keydown:function(a){var b=a.target,c=b.type;(a.keyCode===13&&b.nodeName.toLowerCase()!=="textarea"||a.keyCode===32&&(c==="checkbox"||c==="radio")||c==="select-multiple")&&D.call(this,a)},beforeactivate:function(a){var b=a.target;d._data(b,"_change_data",C(b))}},setup:function(a,b){if(this.type==="file")return!1;for(var c in B)d.event.add(this,c+".specialChange",B[c]);return s.test(this.nodeName)},teardown:function(a){d.event.remove(this,".specialChange");return s.test(this.nodeName)}},B=d.event.special.change.filters,B.focus=B.beforeactivate}c.addEventListener&&d.each({focus:"focusin",blur:"focusout"},function(a,b){function f(a){var c=d.event.fix(a);c.type=b,c.originalEvent={},d.event.trigger(c,null,c.target),c.isDefaultPrevented()&&a.preventDefault()}var e=0;d.event.special[b]={setup:function(){e++===0&&c.addEventListener(a,f,!0)},teardown:function(){--e===0&&c.removeEventListener(a,f,!0)}}}),d.each(["bind","one"],function(a,c){d.fn[c]=function(a,e,f){if(typeof a==="object"){for(var g in a)this[c](g,e,a[g],f);return this}if(d.isFunction(e)||e===!1)f=e,e=b;var h=c==="one"?d.proxy(f,function(a){d(this).unbind(a,h);return f.apply(this,arguments)}):f;if(a==="unload"&&c!=="one")this.one(a,e,f);else for(var i=0,j=this.length;i<j;i++)d.event.add(this[i],a,h,e);return this}}),d.fn.extend({unbind:function(a,b){if(typeof a!=="object"||a.preventDefault)for(var e=0,f=this.length;e<f;e++)d.event.remove(this[e],a,b);else for(var c in a)this.unbind(c,a[c]);return this},delegate:function(a,b,c,d){return this.live(b,c,d,a)},undelegate:function(a,b,c){return arguments.length===0?this.unbind("live"):this.die(b,null,c,a)},trigger:function(a,b){return this.each(function(){d.event.trigger(a,b,this)})},triggerHandler:function(a,b){if(this[0]){var c=d.Event(a);c.preventDefault(),c.stopPropagation(),d.event.trigger(c,b,this[0]);return c.result}},toggle:function(a){var b=arguments,c=1;while(c<b.length)d.proxy(a,b[c++]);return this.click(d.proxy(a,function(e){var f=(d._data(this,"lastToggle"+a.guid)||0)%c;d._data(this,"lastToggle"+a.guid,f+1),e.preventDefault();return b[f].apply(this,arguments)||!1}))},hover:function(a,b){return this.mouseenter(a).mouseleave(b||a)}});var F={focus:"focusin",blur:"focusout",mouseenter:"mouseover",mouseleave:"mouseout"};d.each(["live","die"],function(a,c){d.fn[c]=function(a,e,f,g){var h,i=0,j,k,l,m=g||this.selector,n=g?this:d(this.context);if(typeof a==="object"&&!a.preventDefault){for(var o in a)n[c](o,e,a[o],m);return this}d.isFunction(e)&&(f=e,e=b),a=(a||"").split(" ");while((h=a[i++])!=null){j=r.exec(h),k="",j&&(k=j[0],h=h.replace(r,""));if(h==="hover"){a.push("mouseenter"+k,"mouseleave"+k);continue}l=h,h==="focus"||h==="blur"?(a.push(F[h]+k),h=h+k):h=(F[h]||h)+k;if(c==="live")for(var p=0,q=n.length;p<q;p++)d.event.add(n[p],"live."+H(h,m),{data:e,selector:m,handler:f,origType:h,origHandler:f,preType:l});else n.unbind("live."+H(h,m),f)}return this}}),d.each("blur focus focusin focusout load resize scroll unload click dblclick mousedown mouseup mousemove mouseover mouseout mouseenter mouseleave change select submit keydown keypress keyup error".split(" "),function(a,b){d.fn[b]=function(a,c){c==null&&(c=a,a=null);return arguments.length>0?this.bind(b,a,c):this.trigger(b)},d.attrFn&&(d.attrFn[b]=!0)}),function(){function u(a,b,c,d,e,f){for(var g=0,h=d.length;g<h;g++){var i=d[g];if(i){var j=!1;i=i[a];while(i){if(i.sizcache===c){j=d[i.sizset];break}if(i.nodeType===1){f||(i.sizcache=c,i.sizset=g);if(typeof b!=="string"){if(i===b){j=!0;break}}else if(k.filter(b,[i]).length>0){j=i;break}}i=i[a]}d[g]=j}}}function t(a,b,c,d,e,f){for(var g=0,h=d.length;g<h;g++){var i=d[g];if(i){var j=!1;i=i[a];while(i){if(i.sizcache===c){j=d[i.sizset];break}i.nodeType===1&&!f&&(i.sizcache=c,i.sizset=g);if(i.nodeName.toLowerCase()===b){j=i;break}i=i[a]}d[g]=j}}}var a=/((?:\((?:\([^()]+\)|[^()]+)+\)|\[(?:\[[^\[\]]*\]|['"][^'"]*['"]|[^\[\]'"]+)+\]|\\.|[^ >+~,(\[\\]+)+|[>+~])(\s*,\s*)?((?:.|\r|\n)*)/g,e=0,f=Object.prototype.toString,g=!1,h=!0,i=/\\/g,j=/\W/;[0,0].sort(function(){h=!1;return 0});var k=function(b,d,e,g){e=e||[],d=d||c;var h=d;if(d.nodeType!==1&&d.nodeType!==9)return[];if(!b||typeof b!=="string")return e;var i,j,n,o,q,r,s,t,u=!0,w=k.isXML(d),x=[],y=b;do{a.exec(""),i=a.exec(y);if(i){y=i[3],x.push(i[1]);if(i[2]){o=i[3];break}}}while(i);if(x.length>1&&m.exec(b))if(x.length===2&&l.relative[x[0]])j=v(x[0]+x[1],d);else{j=l.relative[x[0]]?[d]:k(x.shift(),d);while(x.length)b=x.shift(),l.relative[b]&&(b+=x.shift()),j=v(b,j)}else{!g&&x.length>1&&d.nodeType===9&&!w&&l.match.ID.test(x[0])&&!l.match.ID.test(x[x.length-1])&&(q=k.find(x.shift(),d,w),d=q.expr?k.filter(q.expr,q.set)[0]:q.set[0]);if(d){q=g?{expr:x.pop(),set:p(g)}:k.find(x.pop(),x.length===1&&(x[0]==="~"||x[0]==="+")&&d.parentNode?d.parentNode:d,w),j=q.expr?k.filter(q.expr,q.set):q.set,x.length>0?n=p(j):u=!1;while(x.length)r=x.pop(),s=r,l.relative[r]?s=x.pop():r="",s==null&&(s=d),l.relative[r](n,s,w)}else n=x=[]}n||(n=j),n||k.error(r||b);if(f.call(n)==="[object Array]")if(u)if(d&&d.nodeType===1)for(t=0;n[t]!=null;t++)n[t]&&(n[t]===!0||n[t].nodeType===1&&k.contains(d,n[t]))&&e.push(j[t]);else for(t=0;n[t]!=null;t++)n[t]&&n[t].nodeType===1&&e.push(j[t]);else e.push.apply(e,n);else p(n,e);o&&(k(o,h,e,g),k.uniqueSort(e));return e};k.uniqueSort=function(a){if(r){g=h,a.sort(r);if(g)for(var b=1;b<a.length;b++)a[b]===a[b-1]&&a.splice(b--,1)}return a},k.matches=function(a,b){return k(a,null,null,b)},k.matchesSelector=function(a,b){return k(b,null,null,[a]).length>0},k.find=function(a,b,c){var d;if(!a)return[];for(var e=0,f=l.order.length;e<f;e++){var g,h=l.order[e];if(g=l.leftMatch[h].exec(a)){var j=g[1];g.splice(1,1);if(j.substr(j.length-1)!=="\\"){g[1]=(g[1]||"").replace(i,""),d=l.find[h](g,b,c);if(d!=null){a=a.replace(l.match[h],"");break}}}}d||(d=typeof b.getElementsByTagName!=="undefined"?b.getElementsByTagName("*"):[]);return{set:d,expr:a}},k.filter=function(a,c,d,e){var f,g,h=a,i=[],j=c,m=c&&c[0]&&k.isXML(c[0]);while(a&&c.length){for(var n in l.filter)if((f=l.leftMatch[n].exec(a))!=null&&f[2]){var o,p,q=l.filter[n],r=f[1];g=!1,f.splice(1,1);if(r.substr(r.length-1)==="\\")continue;j===i&&(i=[]);if(l.preFilter[n]){f=l.preFilter[n](f,j,d,i,e,m);if(f){if(f===!0)continue}else g=o=!0}if(f)for(var s=0;(p=j[s])!=null;s++)if(p){o=q(p,f,s,j);var t=e^!!o;d&&o!=null?t?g=!0:j[s]=!1:t&&(i.push(p),g=!0)}if(o!==b){d||(j=i),a=a.replace(l.match[n],"");if(!g)return[];break}}if(a===h)if(g==null)k.error(a);else break;h=a}return j},k.error=function(a){throw"Syntax error, unrecognized expression: "+a};var l=k.selectors={order:["ID","NAME","TAG"],match:{ID:/#((?:[\w\u00c0-\uFFFF\-]|\\.)+)/,CLASS:/\.((?:[\w\u00c0-\uFFFF\-]|\\.)+)/,NAME:/\[name=['"]*((?:[\w\u00c0-\uFFFF\-]|\\.)+)['"]*\]/,ATTR:/\[\s*((?:[\w\u00c0-\uFFFF\-]|\\.)+)\s*(?:(\S?=)\s*(?:(['"])(.*?)\3|(#?(?:[\w\u00c0-\uFFFF\-]|\\.)*)|)|)\s*\]/,TAG:/^((?:[\w\u00c0-\uFFFF\*\-]|\\.)+)/,CHILD:/:(only|nth|last|first)-child(?:\(\s*(even|odd|(?:[+\-]?\d+|(?:[+\-]?\d*)?n\s*(?:[+\-]\s*\d+)?))\s*\))?/,POS:/:(nth|eq|gt|lt|first|last|even|odd)(?:\((\d*)\))?(?=[^\-]|$)/,PSEUDO:/:((?:[\w\u00c0-\uFFFF\-]|\\.)+)(?:\((['"]?)((?:\([^\)]+\)|[^\(\)]*)+)\2\))?/},leftMatch:{},attrMap:{"class":"className","for":"htmlFor"},attrHandle:{href:function(a){return a.getAttribute("href")},type:function(a){return a.getAttribute("type")}},relative:{"+":function(a,b){var c=typeof b==="string",d=c&&!j.test(b),e=c&&!d;d&&(b=b.toLowerCase());for(var f=0,g=a.length,h;f<g;f++)if(h=a[f]){while((h=h.previousSibling)&&h.nodeType!==1){}a[f]=e||h&&h.nodeName.toLowerCase()===b?h||!1:h===b}e&&k.filter(b,a,!0)},">":function(a,b){var c,d=typeof b==="string",e=0,f=a.length;if(d&&!j.test(b)){b=b.toLowerCase();for(;e<f;e++){c=a[e];if(c){var g=c.parentNode;a[e]=g.nodeName.toLowerCase()===b?g:!1}}}else{for(;e<f;e++)c=a[e],c&&(a[e]=d?c.parentNode:c.parentNode===b);d&&k.filter(b,a,!0)}},"":function(a,b,c){var d,f=e++,g=u;typeof b==="string"&&!j.test(b)&&(b=b.toLowerCase(),d=b,g=t),g("parentNode",b,f,a,d,c)},"~":function(a,b,c){var d,f=e++,g=u;typeof b==="string"&&!j.test(b)&&(b=b.toLowerCase(),d=b,g=t),g("previousSibling",b,f,a,d,c)}},find:{ID:function(a,b,c){if(typeof b.getElementById!=="undefined"&&!c){var d=b.getElementById(a[1]);return d&&d.parentNode?[d]:[]}},NAME:function(a,b){if(typeof b.getElementsByName!=="undefined"){var c=[],d=b.getElementsByName(a[1]);for(var e=0,f=d.length;e<f;e++)d[e].getAttribute("name")===a[1]&&c.push(d[e]);return c.length===0?null:c}},TAG:function(a,b){if(typeof b.getElementsByTagName!=="undefined")return b.getElementsByTagName(a[1])}},preFilter:{CLASS:function(a,b,c,d,e,f){a=" "+a[1].replace(i,"")+" ";if(f)return a;for(var g=0,h;(h=b[g])!=null;g++)h&&(e^(h.className&&(" "+h.className+" ").replace(/[\t\n\r]/g," ").indexOf(a)>=0)?c||d.push(h):c&&(b[g]=!1));return!1},ID:function(a){return a[1].replace(i,"")},TAG:function(a,b){return a[1].replace(i,"").toLowerCase()},CHILD:function(a){if(a[1]==="nth"){a[2]||k.error(a[0]),a[2]=a[2].replace(/^\+|\s*/g,"");var b=/(-?)(\d*)(?:n([+\-]?\d*))?/.exec(a[2]==="even"&&"2n"||a[2]==="odd"&&"2n+1"||!/\D/.test(a[2])&&"0n+"+a[2]||a[2]);a[2]=b[1]+(b[2]||1)-0,a[3]=b[3]-0}else a[2]&&k.error(a[0]);a[0]=e++;return a},ATTR:function(a,b,c,d,e,f){var g=a[1]=a[1].replace(i,"");!f&&l.attrMap[g]&&(a[1]=l.attrMap[g]),a[4]=(a[4]||a[5]||"").replace(i,""),a[2]==="~="&&(a[4]=" "+a[4]+" ");return a},PSEUDO:function(b,c,d,e,f){if(b[1]==="not")if((a.exec(b[3])||"").length>1||/^\w/.test(b[3]))b[3]=k(b[3],null,null,c);else{var g=k.filter(b[3],c,d,!0^f);d||e.push.apply(e,g);return!1}else if(l.match.POS.test(b[0])||l.match.CHILD.test(b[0]))return!0;return b},POS:function(a){a.unshift(!0);return a}},filters:{enabled:function(a){return a.disabled===!1&&a.type!=="hidden"},disabled:function(a){return a.disabled===!0},checked:function(a){return a.checked===!0},selected:function(a){a.parentNode&&a.parentNode.selectedIndex;return a.selected===!0},parent:function(a){return!!a.firstChild},empty:function(a){return!a.firstChild},has:function(a,b,c){return!!k(c[3],a).length},header:function(a){return/h\d/i.test(a.nodeName)},text:function(a){var b=a.getAttribute("type"),c=a.type;return"text"===c&&(b===c||b===null)},radio:function(a){return"radio"===a.type},checkbox:function(a){return"checkbox"===a.type},file:function(a){return"file"===a.type},password:function(a){return"password"===a.type},submit:function(a){return"submit"===a.type},image:function(a){return"image"===a.type},reset:function(a){return"reset"===a.type},button:function(a){return"button"===a.type||a.nodeName.toLowerCase()==="button"},input:function(a){return/input|select|textarea|button/i.test(a.nodeName)}},setFilters:{first:function(a,b){return b===0},last:function(a,b,c,d){return b===d.length-1},even:function(a,b){return b%2===0},odd:function(a,b){return b%2===1},lt:function(a,b,c){return b<c[3]-0},gt:function(a,b,c){return b>c[3]-0},nth:function(a,b,c){return c[3]-0===b},eq:function(a,b,c){return c[3]-0===b}},filter:{PSEUDO:function(a,b,c,d){var e=b[1],f=l.filters[e];if(f)return f(a,c,b,d);if(e==="contains")return(a.textContent||a.innerText||k.getText([a])||"").indexOf(b[3])>=0;if(e==="not"){var g=b[3];for(var h=0,i=g.length;h<i;h++)if(g[h]===a)return!1;return!0}k.error(e)},CHILD:function(a,b){var c=b[1],d=a;switch(c){case"only":case"first":while(d=d.previousSibling)if(d.nodeType===1)return!1;if(c==="first")return!0;d=a;case"last":while(d=d.nextSibling)if(d.nodeType===1)return!1;return!0;case"nth":var e=b[2],f=b[3];if(e===1&&f===0)return!0;var g=b[0],h=a.parentNode;if(h&&(h.sizcache!==g||!a.nodeIndex)){var i=0;for(d=h.firstChild;d;d=d.nextSibling)d.nodeType===1&&(d.nodeIndex=++i);h.sizcache=g}var j=a.nodeIndex-f;return e===0?j===0:j%e===0&&j/e>=0}},ID:function(a,b){return a.nodeType===1&&a.getAttribute("id")===b},TAG:function(a,b){return b==="*"&&a.nodeType===1||a.nodeName.toLowerCase()===b},CLASS:function(a,b){return(" "+(a.className||a.getAttribute("class"))+" ").indexOf(b)>-1},ATTR:function(a,b){var c=b[1],d=l.attrHandle[c]?l.attrHandle[c](a):a[c]!=null?a[c]:a.getAttribute(c),e=d+"",f=b[2],g=b[4];return d==null?f==="!=":f==="="?e===g:f==="*="?e.indexOf(g)>=0:f==="~="?(" "+e+" ").indexOf(g)>=0:g?f==="!="?e!==g:f==="^="?e.indexOf(g)===0:f==="$="?e.substr(e.length-g.length)===g:f==="|="?e===g||e.substr(0,g.length+1)===g+"-":!1:e&&d!==!1},POS:function(a,b,c,d){var e=b[2],f=l.setFilters[e];if(f)return f(a,c,b,d)}}},m=l.match.POS,n=function(a,b){return"\\"+(b-0+1)};for(var o in l.match)l.match[o]=new RegExp(l.match[o].source+/(?![^\[]*\])(?![^\(]*\))/.source),l.leftMatch[o]=new RegExp(/(^(?:.|\r|\n)*?)/.source+l.match[o].source.replace(/\\(\d+)/g,n));var p=function(a,b){a=Array.prototype.slice.call(a,0);if(b){b.push.apply(b,a);return b}return a};try{Array.prototype.slice.call(c.documentElement.childNodes,0)[0].nodeType}catch(q){p=function(a,b){var c=0,d=b||[];if(f.call(a)==="[object Array]")Array.prototype.push.apply(d,a);else if(typeof a.length==="number")for(var e=a.length;c<e;c++)d.push(a[c]);else for(;a[c];c++)d.push(a[c]);return d}}var r,s;c.documentElement.compareDocumentPosition?r=function(a,b){if(a===b){g=!0;return 0}if(!a.compareDocumentPosition||!b.compareDocumentPosition)return a.compareDocumentPosition?-1:1;return a.compareDocumentPosition(b)&4?-1:1}:(r=function(a,b){var c,d,e=[],f=[],h=a.parentNode,i=b.parentNode,j=h;if(a===b){g=!0;return 0}if(h===i)return s(a,b);if(!h)return-1;if(!i)return 1;while(j)e.unshift(j),j=j.parentNode;j=i;while(j)f.unshift(j),j=j.parentNode;c=e.length,d=f.length;for(var k=0;k<c&&k<d;k++)if(e[k]!==f[k])return s(e[k],f[k]);return k===c?s(a,f[k],-1):s(e[k],b,1)},s=function(a,b,c){if(a===b)return c;var d=a.nextSibling;while(d){if(d===b)return-1;d=d.nextSibling}return 1}),k.getText=function(a){var b="",c;for(var d=0;a[d];d++)c=a[d],c.nodeType===3||c.nodeType===4?b+=c.nodeValue:c.nodeType!==8&&(b+=k.getText(c.childNodes));return b},function(){var a=c.createElement("div"),d="script"+(new Date).getTime(),e=c.documentElement;a.innerHTML="<a name='"+d+"'/>",e.insertBefore(a,e.firstChild),c.getElementById(d)&&(l.find.ID=function(a,c,d){if(typeof c.getElementById!=="undefined"&&!d){var e=c.getElementById(a[1]);return e?e.id===a[1]||typeof e.getAttributeNode!=="undefined"&&e.getAttributeNode("id").nodeValue===a[1]?[e]:b:[]}},l.filter.ID=function(a,b){var c=typeof a.getAttributeNode!=="undefined"&&a.getAttributeNode("id");return a.nodeType===1&&c&&c.nodeValue===b}),e.removeChild(a),e=a=null}(),function(){var a=c.createElement("div");a.appendChild(c.createComment("")),a.getElementsByTagName("*").length>0&&(l.find.TAG=function(a,b){var c=b.getElementsByTagName(a[1]);if(a[1]==="*"){var d=[];for(var e=0;c[e];e++)c[e].nodeType===1&&d.push(c[e]);c=d}return c}),a.innerHTML="<a href='#'></a>",a.firstChild&&typeof a.firstChild.getAttribute!=="undefined"&&a.firstChild.getAttribute("href")!=="#"&&(l.attrHandle.href=function(a){return a.getAttribute("href",2)}),a=null}(),c.querySelectorAll&&function(){var a=k,b=c.createElement("div"),d="__sizzle__";b.innerHTML="<p class='TEST'></p>";if(!b.querySelectorAll||b.querySelectorAll(".TEST").length!==0){k=function(b,e,f,g){e=e||c;if(!g&&!k.isXML(e)){var h=/^(\w+$)|^\.([\w\-]+$)|^#([\w\-]+$)/.exec(b);if(h&&(e.nodeType===1||e.nodeType===9)){if(h[1])return p(e.getElementsByTagName(b),f);if(h[2]&&l.find.CLASS&&e.getElementsByClassName)return p(e.getElementsByClassName(h[2]),f)}if(e.nodeType===9){if(b==="body"&&e.body)return p([e.body],f);if(h&&h[3]){var i=e.getElementById(h[3]);if(!i||!i.parentNode)return p([],f);if(i.id===h[3])return p([i],f)}try{return p(e.querySelectorAll(b),f)}catch(j){}}else if(e.nodeType===1&&e.nodeName.toLowerCase()!=="object"){var m=e,n=e.getAttribute("id"),o=n||d,q=e.parentNode,r=/^\s*[+~]/.test(b);n?o=o.replace(/'/g,"\\$&"):e.setAttribute("id",o),r&&q&&(e=e.parentNode);try{if(!r||q)return p(e.querySelectorAll("[id='"+o+"'] "+b),f)}catch(s){}finally{n||m.removeAttribute("id")}}}return a(b,e,f,g)};for(var e in a)k[e]=a[e];b=null}}(),function(){var a=c.documentElement,b=a.matchesSelector||a.mozMatchesSelector||a.webkitMatchesSelector||a.msMatchesSelector;if(b){var d=!b.call(c.createElement("div"),"div"),e=!1;try{b.call(c.documentElement,"[test!='']:sizzle")}catch(f){e=!0}k.matchesSelector=function(a,c){c=c.replace(/\=\s*([^'"\]]*)\s*\]/g,"='$1']");if(!k.isXML(a))try{if(e||!l.match.PSEUDO.test(c)&&!/!=/.test(c)){var f=b.call(a,c);if(f||!d||a.document&&a.document.nodeType!==11)return f}}catch(g){}return k(c,null,null,[a]).length>0}}}(),function(){var a=c.createElement("div");a.innerHTML="<div class='test e'></div><div class='test'></div>";if(a.getElementsByClassName&&a.getElementsByClassName("e").length!==0){a.lastChild.className="e";if(a.getElementsByClassName("e").length===1)return;l.order.splice(1,0,"CLASS"),l.find.CLASS=function(a,b,c){if(typeof b.getElementsByClassName!=="undefined"&&!c)return b.getElementsByClassName(a[1])},a=null}}(),c.documentElement.contains?k.contains=function(a,b){return a!==b&&(a.contains?a.contains(b):!0)}:c.documentElement.compareDocumentPosition?k.contains=function(a,b){return!!(a.compareDocumentPosition(b)&16)}:k.contains=function(){return!1},k.isXML=function(a){var b=(a?a.ownerDocument||a:0).documentElement;return b?b.nodeName!=="HTML":!1};var v=function(a,b){var c,d=[],e="",f=b.nodeType?[b]:b;while(c=l.match.PSEUDO.exec(a))e+=c[0],a=a.replace(l.match.PSEUDO,"");a=l.relative[a]?a+"*":a;for(var g=0,h=f.length;g<h;g++)k(a,f[g],d);return k.filter(e,d)};d.find=k,d.expr=k.selectors,d.expr[":"]=d.expr.filters,d.unique=k.uniqueSort,d.text=k.getText,d.isXMLDoc=k.isXML,d.contains=k.contains}();var I=/Until$/,J=/^(?:parents|prevUntil|prevAll)/,K=/,/,L=/^.[^:#\[\.,]*$/,M=Array.prototype.slice,N=d.expr.match.POS,O={children:!0,contents:!0,next:!0,prev:!0};d.fn.extend({find:function(a){var b=this.pushStack("","find",a),c=0;for(var e=0,f=this.length;e<f;e++){c=b.length,d.find(a,this[e],b);if(e>0)for(var g=c;g<b.length;g++)for(var h=0;h<c;h++)if(b[h]===b[g]){b.splice(g--,1);break}}return b},has:function(a){var b=d(a);return this.filter(function(){for(var a=0,c=b.length;a<c;a++)if(d.contains(this,b[a]))return!0})},not:function(a){return this.pushStack(Q(this,a,!1),"not",a)},filter:function(a){return this.pushStack(Q(this,a,!0),"filter",a)},is:function(a){return!!a&&d.filter(a,this).length>0},closest:function(a,b){var c=[],e,f,g=this[0];if(d.isArray(a)){var h,i,j={},k=1;if(g&&a.length){for(e=0,f=a.length;e<f;e++)i=a[e],j[i]||(j[i]=d.expr.match.POS.test(i)?d(i,b||this.context):i);while(g&&g.ownerDocument&&g!==b){for(i in j)h=j[i],(h.jquery?h.index(g)>-1:d(g).is(h))&&c.push({selector:i,elem:g,level:k});g=g.parentNode,k++}}return c}var l=N.test(a)?d(a,b||this.context):null;for(e=0,f=this.length;e<f;e++){g=this[e];while(g){if(l?l.index(g)>-1:d.find.matchesSelector(g,a)){c.push(g);break}g=g.parentNode;if(!g||!g.ownerDocument||g===b)break}}c=c.length>1?d.unique(c):c;return this.pushStack(c,"closest",a)},index:function(a){if(!a||typeof a==="string")return d.inArray(this[0],a?d(a):this.parent().children());return d.inArray(a.jquery?a[0]:a,this)},add:function(a,b){var c=typeof a==="string"?d(a,b):d.makeArray(a),e=d.merge(this.get(),c);return this.pushStack(P(c[0])||P(e[0])?e:d.unique(e))},andSelf:function(){return this.add(this.prevObject)}}),d.each({parent:function(a){var b=a.parentNode;return b&&b.nodeType!==11?b:null},parents:function(a){return d.dir(a,"parentNode")},parentsUntil:function(a,b,c){return d.dir(a,"parentNode",c)},next:function(a){return d.nth(a,2,"nextSibling")},prev:function(a){return d.nth(a,2,"previousSibling")},nextAll:function(a){return d.dir(a,"nextSibling")},prevAll:function(a){return d.dir(a,"previousSibling")},nextUntil:function(a,b,c){return d.dir(a,"nextSibling",c)},prevUntil:function(a,b,c){return d.dir(a,"previousSibling",c)},siblings:function(a){return d.sibling(a.parentNode.firstChild,a)},children:function(a){return d.sibling(a.firstChild)},contents:function(a){return d.nodeName(a,"iframe")?a.contentDocument||a.contentWindow.document:d.makeArray(a.childNodes)}},function(a,b){d.fn[a]=function(c,e){var f=d.map(this,b,c),g=M.call(arguments);I.test(a)||(e=c),e&&typeof e==="string"&&(f=d.filter(e,f)),f=this.length>1&&!O[a]?d.unique(f):f,(this.length>1||K.test(e))&&J.test(a)&&(f=f.reverse());return this.pushStack(f,a,g.join(","))}}),d.extend({filter:function(a,b,c){c&&(a=":not("+a+")");return b.length===1?d.find.matchesSelector(b[0],a)?[b[0]]:[]:d.find.matches(a,b)},dir:function(a,c,e){var f=[],g=a[c];while(g&&g.nodeType!==9&&(e===b||g.nodeType!==1||!d(g).is(e)))g.nodeType===1&&f.push(g),g=g[c];return f},nth:function(a,b,c,d){b=b||1;var e=0;for(;a;a=a[c])if(a.nodeType===1&&++e===b)break;return a},sibling:function(a,b){var c=[];for(;a;a=a.nextSibling)a.nodeType===1&&a!==b&&c.push(a);return c}});var R=/ jQuery\d+="(?:\d+|null)"/g,S=/^\s+/,T=/<(?!area|br|col|embed|hr|img|input|link|meta|param)(([\w:]+)[^>]*)\/>/ig,U=/<([\w:]+)/,V=/<tbody/i,W=/<|&#?\w+;/,X=/<(?:script|object|embed|option|style)/i,Y=/checked\s*(?:[^=]|=\s*.checked.)/i,Z={option:[1,"<select multiple='multiple'>","</select>"],legend:[1,"<fieldset>","</fieldset>"],thead:[1,"<table>","</table>"],tr:[2,"<table><tbody>","</tbody></table>"],td:[3,"<table><tbody><tr>","</tr></tbody></table>"],col:[2,"<table><tbody></tbody><colgroup>","</colgroup></table>"],area:[1,"<map>","</map>"],_default:[0,"",""]};Z.optgroup=Z.option,Z.tbody=Z.tfoot=Z.colgroup=Z.caption=Z.thead,Z.th=Z.td,d.support.htmlSerialize||(Z._default=[1,"div<div>","</div>"]),d.fn.extend({text:function(a){if(d.isFunction(a))return this.each(function(b){var c=d(this);c.text(a.call(this,b,c.text()))});if(typeof a!=="object"&&a!==b)return this.empty().append((this[0]&&this[0].ownerDocument||c).createTextNode(a));return d.text(this)},wrapAll:function(a){if(d.isFunction(a))return this.each(function(b){d(this).wrapAll(a.call(this,b))});if(this[0]){var b=d(a,this[0].ownerDocument).eq(0).clone(!0);this[0].parentNode&&b.insertBefore(this[0]),b.map(function(){var a=this;while(a.firstChild&&a.firstChild.nodeType===1)a=a.firstChild;return a}).append(this)}return this},wrapInner:function(a){if(d.isFunction(a))return this.each(function(b){d(this).wrapInner(a.call(this,b))});return this.each(function(){var b=d(this),c=b.contents();c.length?c.wrapAll(a):b.append(a)})},wrap:function(a){return this.each(function(){d(this).wrapAll(a)})},unwrap:function(){return this.parent().each(function(){d.nodeName(this,"body")||d(this).replaceWith(this.childNodes)}).end()},append:function(){return this.domManip(arguments,!0,function(a){this.nodeType===1&&this.appendChild(a)})},prepend:function(){return this.domManip(arguments,!0,function(a){this.nodeType===1&&this.insertBefore(a,this.firstChild)})},before:function(){if(this[0]&&this[0].parentNode)return this.domManip(arguments,!1,function(a){this.parentNode.insertBefore(a,this)});if(arguments.length){var a=d(arguments[0]);a.push.apply(a,this.toArray());return this.pushStack(a,"before",arguments)}},after:function(){if(this[0]&&this[0].parentNode)return this.domManip(arguments,!1,function(a){this.parentNode.insertBefore(a,this.nextSibling)});if(arguments.length){var a=this.pushStack(this,"after",arguments);a.push.apply(a,d(arguments[0]).toArray());return a}},remove:function(a,b){for(var c=0,e;(e=this[c])!=null;c++)if(!a||d.filter(a,[e]).length)!b&&e.nodeType===1&&(d.cleanData(e.getElementsByTagName("*")),d.cleanData([e])),e.parentNode&&e.parentNode.removeChild(e);return this},empty:function(){for(var a=0,b;(b=this[a])!=null;a++){b.nodeType===1&&d.cleanData(b.getElementsByTagName("*"));while(b.firstChild)b.removeChild(b.firstChild)}return this},clone:function(a,b){a=a==null?!1:a,b=b==null?a:b;return this.map(function(){return d.clone(this,a,b)})},html:function(a){if(a===b)return this[0]&&this[0].nodeType===1?this[0].innerHTML.replace(R,""):null;if(typeof a!=="string"||X.test(a)||!d.support.leadingWhitespace&&S.test(a)||Z[(U.exec(a)||["",""])[1].toLowerCase()])d.isFunction(a)?this.each(function(b){var c=d(this);c.html(a.call(this,b,c.html()))}):this.empty().append(a);else{a=a.replace(T,"<$1></$2>");try{for(var c=0,e=this.length;c<e;c++)this[c].nodeType===1&&(d.cleanData(this[c].getElementsByTagName("*")),this[c].innerHTML=a)}catch(f){this.empty().append(a)}}return this},replaceWith:function(a){if(this[0]&&this[0].parentNode){if(d.isFunction(a))return this.each(function(b){var c=d(this),e=c.html();c.replaceWith(a.call(this,b,e))});typeof a!=="string"&&(a=d(a).detach());return this.each(function(){var b=this.nextSibling,c=this.parentNode;d(this).remove(),b?d(b).before(a):d(c).append(a)})}return this.length?this.pushStack(d(d.isFunction(a)?a():a),"replaceWith",a):this},detach:function(a){return this.remove(a,!0)},domManip:function(a,c,e){var f,g,h,i,j=a[0],k=[];if(!d.support.checkClone&&arguments.length===3&&typeof j==="string"&&Y.test(j))return this.each(function(){d(this).domManip(a,c,e,!0)});if(d.isFunction(j))return this.each(function(f){var g=d(this);a[0]=j.call(this,f,c?g.html():b),g.domManip(a,c,e)});if(this[0]){i=j&&j.parentNode,d.support.parentNode&&i&&i.nodeType===11&&i.childNodes.length===this.length?f={fragment:i}:f=d.buildFragment(a,this,k),h=f.fragment,h.childNodes.length===1?g=h=h.firstChild:g=h.firstChild;if(g){c=c&&d.nodeName(g,"tr");for(var l=0,m=this.length,n=m-1;l<m;l++)e.call(c?$(this[l],g):this[l],f.cacheable||m>1&&l<n?d.clone(h,!0,!0):h)}k.length&&d.each(k,bc)}return this}}),d.buildFragment=function(a,b,e){var f,g,h,i=b&&b[0]?b[0].ownerDocument||b[0]:c;a.length===1&&typeof a[0]==="string"&&a[0].length<512&&i===c&&a[0].charAt(0)==="<"&&!X.test(a[0])&&(d.support.checkClone||!Y.test(a[0]))&&(g=!0,h=d.fragments[a[0]],h&&(h!==1&&(f=h))),f||(f=i.createDocumentFragment(),d.clean(a,i,f,e)),g&&(d.fragments[a[0]]=h?f:1);return{fragment:f,cacheable:g}},d.fragments={},d.each({appendTo:"append",prependTo:"prepend",insertBefore:"before",insertAfter:"after",replaceAll:"replaceWith"},function(a,b){d.fn[a]=function(c){var e=[],f=d(c),g=this.length===1&&this[0].parentNode;if(g&&g.nodeType===11&&g.childNodes.length===1&&f.length===1){f[b](this[0]);return this}for(var h=0,i=f.length;h<i;h++){var j=(h>0?this.clone(!0):this).get();d(f[h])[b](j),e=e.concat(j)}return this.pushStack(e,a,f.selector)}}),d.extend({clone:function(a,b,c){var e=a.cloneNode(!0),f,g,h;if((!d.support.noCloneEvent||!d.support.noCloneChecked)&&(a.nodeType===1||a.nodeType===11)&&!d.isXMLDoc(a)){ba(a,e),f=bb(a),g=bb(e);for(h=0;f[h];++h)ba(f[h],g[h])}if(b){_(a,e);if(c){f=bb(a),g=bb(e);for(h=0;f[h];++h)_(f[h],g[h])}}return e},clean:function(a,b,e,f){b=b||c,typeof b.createElement==="undefined"&&(b=b.ownerDocument||b[0]&&b[0].ownerDocument||c);var g=[];for(var h=0,i;(i=a[h])!=null;h++){typeof i==="number"&&(i+="");if(!i)continue;if(typeof i!=="string"||W.test(i)){if(typeof i==="string"){i=i.replace(T,"<$1></$2>");var j=(U.exec(i)||["",""])[1].toLowerCase(),k=Z[j]||Z._default,l=k[0],m=b.createElement("div");m.innerHTML=k[1]+i+k[2];while(l--)m=m.lastChild;if(!d.support.tbody){var n=V.test(i),o=j==="table"&&!n?m.firstChild&&m.firstChild.childNodes:k[1]==="<table>"&&!n?m.childNodes:[];for(var p=o.length-1;p>=0;--p)d.nodeName(o[p],"tbody")&&!o[p].childNodes.length&&o[p].parentNode.removeChild(o[p])}!d.support.leadingWhitespace&&S.test(i)&&m.insertBefore(b.createTextNode(S.exec(i)[0]),m.firstChild),i=m.childNodes}}else i=b.createTextNode(i);i.nodeType?g.push(i):g=d.merge(g,i)}if(e)for(h=0;g[h];h++)!f||!d.nodeName(g[h],"script")||g[h].type&&g[h].type.toLowerCase()!=="text/javascript"?(g[h].nodeType===1&&g.splice.apply(g,[h+1,0].concat(d.makeArray(g[h].getElementsByTagName("script")))),e.appendChild(g[h])):f.push(g[h].parentNode?g[h].parentNode.removeChild(g[h]):g[h]);return g},cleanData:function(a){var b,c,e=d.cache,f=d.expando,g=d.event.special,h=d.support.deleteExpando;for(var i=0,j;(j=a[i])!=null;i++){if(j.nodeName&&d.noData[j.nodeName.toLowerCase()])continue;c=j[d.expando];if(c){b=e[c]&&e[c][f];if(b&&b.events){for(var k in b.events)g[k]?d.event.remove(j,k):d.removeEvent(j,k,b.handle);b.handle&&(b.handle.elem=null)}h?delete j[d.expando]:j.removeAttribute&&j.removeAttribute(d.expando),delete e[c]}}}});var bd=/alpha\([^)]*\)/i,be=/opacity=([^)]*)/,bf=/-([a-z])/ig,bg=/([A-Z]|^ms)/g,bh=/^-?\d+(?:px)?$/i,bi=/^-?\d/,bj={position:"absolute",visibility:"hidden",display:"block"},bk=["Left","Right"],bl=["Top","Bottom"],bm,bn,bo,bp=function(a,b){return b.toUpperCase()};d.fn.css=function(a,c){if(arguments.length===2&&c===b)return this;return d.access(this,a,c,!0,function(a,c,e){return e!==b?d.style(a,c,e):d.css(a,c)})},d.extend({cssHooks:{opacity:{get:function(a,b){if(b){var c=bm(a,"opacity","opacity");return c===""?"1":c}return a.style.opacity}}},cssNumber:{zIndex:!0,fontWeight:!0,opacity:!0,zoom:!0,lineHeight:!0},cssProps:{"float":d.support.cssFloat?"cssFloat":"styleFloat"},style:function(a,c,e,f){if(a&&a.nodeType!==3&&a.nodeType!==8&&a.style){var g,h=d.camelCase(c),i=a.style,j=d.cssHooks[h];c=d.cssProps[h]||h;if(e===b){if(j&&"get"in j&&(g=j.get(a,!1,f))!==b)return g;return i[c]}if(typeof e==="number"&&isNaN(e)||e==null)return;typeof e==="number"&&!d.cssNumber[h]&&(e+="px");if(!j||!("set"in j)||(e=j.set(a,e))!==b)try{i[c]=e}catch(k){}}},css:function(a,c,e){var f,g=d.camelCase(c),h=d.cssHooks[g];c=d.cssProps[g]||g;if(h&&"get"in h&&(f=h.get(a,!0,e))!==b)return f;if(bm)return bm(a,c,g)},swap:function(a,b,c){var d={};for(var e in b)d[e]=a.style[e],a.style[e]=b[e];c.call(a);for(e in b)a.style[e]=d[e]},camelCase:function(a){return a.replace(bf,bp)}}),d.curCSS=d.css,d.each(["height","width"],function(a,b){d.cssHooks[b]={get:function(a,c,e){var f;if(c){a.offsetWidth!==0?f=bq(a,b,e):d.swap(a,bj,function(){f=bq(a,b,e)});if(f<=0){f=bm(a,b,b),f==="0px"&&bo&&(f=bo(a,b,b));if(f!=null)return f===""||f==="auto"?"0px":f}if(f<0||f==null){f=a.style[b];return f===""||f==="auto"?"0px":f}return typeof f==="string"?f:f+"px"}},set:function(a,b){if(!bh.test(b))return b;b=parseFloat(b);if(b>=0)return b+"px"}}}),d.support.opacity||(d.cssHooks.opacity={get:function(a,b){return be.test((b&&a.currentStyle?a.currentStyle.filter:a.style.filter)||"")?parseFloat(RegExp.$1)/100+"":b?"1":""},set:function(a,b){var c=a.style;c.zoom=1;var e=d.isNaN(b)?"":"alpha(opacity="+b*100+")",f=c.filter||"";c.filter=bd.test(f)?f.replace(bd,e):c.filter+" "+e}}),d(function(){d.support.reliableMarginRight||(d.cssHooks.marginRight={get:function(a,b){var c;d.swap(a,{display:"inline-block"},function(){b?c=bm(a,"margin-right","marginRight"):c=a.style.marginRight});return c}})}),c.defaultView&&c.defaultView.getComputedStyle&&(bn=function(a,c,e){var f,g,h;e=e.replace(bg,"-$1").toLowerCase();if(!(g=a.ownerDocument.defaultView))return b;if(h=g.getComputedStyle(a,null))f=h.getPropertyValue(e),f===""&&!d.contains(a.ownerDocument.documentElement,a)&&(f=d.style(a,e));return f}),c.documentElement.currentStyle&&(bo=function(a,b){var c,d=a.currentStyle&&a.currentStyle[b],e=a.runtimeStyle&&a.runtimeStyle[b],f=a.style;!bh.test(d)&&bi.test(d)&&(c=f.left,e&&(a.runtimeStyle.left=a.currentStyle.left),f.left=b==="fontSize"?"1em":d||0,d=f.pixelLeft+"px",f.left=c,e&&(a.runtimeStyle.left=e));return d===""?"auto":d}),bm=bn||bo,d.expr&&d.expr.filters&&(d.expr.filters.hidden=function(a){var b=a.offsetWidth,c=a.offsetHeight;return b===0&&c===0||!d.support.reliableHiddenOffsets&&(a.style.display||d.css(a,"display"))==="none"},d.expr.filters.visible=function(a){return!d.expr.filters.hidden(a)});var br=/%20/g,bs=/\[\]$/,bt=/\r?\n/g,bu=/#.*$/,bv=/^(.*?):[ \t]*([^\r\n]*)\r?$/mg,bw=/^(?:color|date|datetime|email|hidden|month|number|password|range|search|tel|text|time|url|week)$/i,bx=/^(?:about|app|app\-storage|.+\-extension|file|widget):$/,by=/^(?:GET|HEAD)$/,bz=/^\/\//,bA=/\?/,bB=/<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi,bC=/^(?:select|textarea)/i,bD=/\s+/,bE=/([?&])_=[^&]*/,bF=/(^|\-)([a-z])/g,bG=function(a,b,c){return b+c.toUpperCase()},bH=/^([\w\+\.\-]+:)(?:\/\/([^\/?#:]*)(?::(\d+))?)?/,bI=d.fn.load,bJ={},bK={},bL,bM;try{bL=c.location.href}catch(bN){bL=c.createElement("a"),bL.href="",bL=bL.href}bM=bH.exec(bL.toLowerCase())||[],d.fn.extend({load:function(a,c,e){if(typeof a!=="string"&&bI)return bI.apply(this,arguments);if(!this.length)return this;var f=a.indexOf(" ");if(f>=0){var g=a.slice(f,a.length);a=a.slice(0,f)}var h="GET";c&&(d.isFunction(c)?(e=c,c=b):typeof c==="object"&&(c=d.param(c,d.ajaxSettings.traditional),h="POST"));var i=this;d.ajax({url:a,type:h,dataType:"html",data:c,complete:function(a,b,c){c=a.responseText,a.isResolved()&&(a.done(function(a){c=a}),i.html(g?d("<div>").append(c.replace(bB,"")).find(g):c)),e&&i.each(e,[c,b,a])}});return this},serialize:function(){return d.param(this.serializeArray())},serializeArray:function(){return this.map(function(){return this.elements?d.makeArray(this.elements):this}).filter(function(){return this.name&&!this.disabled&&(this.checked||bC.test(this.nodeName)||bw.test(this.type))}).map(function(a,b){var c=d(this).val();return c==null?null:d.isArray(c)?d.map(c,function(a,c){return{name:b.name,value:a.replace(bt,"\r\n")}}):{name:b.name,value:c.replace(bt,"\r\n")}}).get()}}),d.each("ajaxStart ajaxStop ajaxComplete ajaxError ajaxSuccess ajaxSend".split(" "),function(a,b){d.fn[b]=function(a){return this.bind(b,a)}}),d.each(["get","post"],function(a,c){d[c]=function(a,e,f,g){d.isFunction(e)&&(g=g||f,f=e,e=b);return d.ajax({type:c,url:a,data:e,success:f,dataType:g})}}),d.extend({getScript:function(a,c){return d.get(a,b,c,"script")},getJSON:function(a,b,c){return d.get(a,b,c,"json")},ajaxSetup:function(a,b){b?d.extend(!0,a,d.ajaxSettings,b):(b=a,a=d.extend(!0,d.ajaxSettings,b));for(var c in {context:1,url:1})c in b?a[c]=b[c]:c in d.ajaxSettings&&(a[c]=d.ajaxSettings[c]);return a},ajaxSettings:{url:bL,isLocal:bx.test(bM[1]),global:!0,type:"GET",contentType:"application/x-www-form-urlencoded",processData:!0,async:!0,accepts:{xml:"application/xml, text/xml",html:"text/html",text:"text/plain",json:"application/json, text/javascript","*":"*/*"},contents:{xml:/xml/,html:/html/,json:/json/},responseFields:{xml:"responseXML",text:"responseText"},converters:{"* text":a.String,"text html":!0,"text json":d.parseJSON,"text xml":d.parseXML}},ajaxPrefilter:bO(bJ),ajaxTransport:bO(bK),ajax:function(a,c){function v(a,c,l,n){if(r!==2){r=2,p&&clearTimeout(p),o=b,m=n||"",u.readyState=a?4:0;var q,t,v,w=l?bR(e,u,l):b,x,y;if(a>=200&&a<300||a===304){if(e.ifModified){if(x=u.getResponseHeader("Last-Modified"))d.lastModified[k]=x;if(y=u.getResponseHeader("Etag"))d.etag[k]=y}if(a===304)c="notmodified",q=!0;else try{t=bS(e,w),c="success",q=!0}catch(z){c="parsererror",v=z}}else{v=c;if(!c||a)c="error",a<0&&(a=0)}u.status=a,u.statusText=c,q?h.resolveWith(f,[t,c,u]):h.rejectWith(f,[u,c,v]),u.statusCode(j),j=b,s&&g.trigger("ajax"+(q?"Success":"Error"),[u,e,q?t:v]),i.resolveWith(f,[u,c]),s&&(g.trigger("ajaxComplete",[u,e]),--d.active||d.event.trigger("ajaxStop"))}}typeof a==="object"&&(c=a,a=b),c=c||{};var e=d.ajaxSetup({},c),f=e.context||e,g=f!==e&&(f.nodeType||f instanceof d)?d(f):d.event,h=d.Deferred(),i=d._Deferred(),j=e.statusCode||{},k,l={},m,n,o,p,q,r=0,s,t,u={readyState:0,setRequestHeader:function(a,b){r||(l[a.toLowerCase().replace(bF,bG)]=b);return this},getAllResponseHeaders:function(){return r===2?m:null},getResponseHeader:function(a){var c;if(r===2){if(!n){n={};while(c=bv.exec(m))n[c[1].toLowerCase()]=c[2]}c=n[a.toLowerCase()]}return c===b?null:c},overrideMimeType:function(a){r||(e.mimeType=a);return this},abort:function(a){a=a||"abort",o&&o.abort(a),v(0,a);return this}};h.promise(u),u.success=u.done,u.error=u.fail,u.complete=i.done,u.statusCode=function(a){if(a){var b;if(r<2)for(b in a)j[b]=[j[b],a[b]];else b=a[u.status],u.then(b,b)}return this},e.url=((a||e.url)+"").replace(bu,"").replace(bz,bM[1]+"//"),e.dataTypes=d.trim(e.dataType||"*").toLowerCase().split(bD),e.crossDomain==null&&(q=bH.exec(e.url.toLowerCase()),e.crossDomain=q&&(q[1]!=bM[1]||q[2]!=bM[2]||(q[3]||(q[1]==="http:"?80:443))!=(bM[3]||(bM[1]==="http:"?80:443)))),e.data&&e.processData&&typeof e.data!=="string"&&(e.data=d.param(e.data,e.traditional)),bP(bJ,e,c,u);if(r===2)return!1;s=e.global,e.type=e.type.toUpperCase(),e.hasContent=!by.test(e.type),s&&d.active++===0&&d.event.trigger("ajaxStart");if(!e.hasContent){e.data&&(e.url+=(bA.test(e.url)?"&":"?")+e.data),k=e.url;if(e.cache===!1){var w=d.now(),x=e.url.replace(bE,"$1_="+w);e.url=x+(x===e.url?(bA.test(e.url)?"&":"?")+"_="+w:"")}}if(e.data&&e.hasContent&&e.contentType!==!1||c.contentType)l["Content-Type"]=e.contentType;e.ifModified&&(k=k||e.url,d.lastModified[k]&&(l["If-Modified-Since"]=d.lastModified[k]),d.etag[k]&&(l["If-None-Match"]=d.etag[k])),l.Accept=e.dataTypes[0]&&e.accepts[e.dataTypes[0]]?e.accepts[e.dataTypes[0]]+(e.dataTypes[0]!=="*"?", */*; q=0.01":""):e.accepts["*"];for(t in e.headers)u.setRequestHeader(t,e.headers[t]);if(e.beforeSend&&(e.beforeSend.call(f,u,e)===!1||r===2)){u.abort();return!1}for(t in {success:1,error:1,complete:1})u[t](e[t]);o=bP(bK,e,c,u);if(o){u.readyState=1,s&&g.trigger("ajaxSend",[u,e]),e.async&&e.timeout>0&&(p=setTimeout(function(){u.abort("timeout")},e.timeout));try{r=1,o.send(l,v)}catch(y){status<2?v(-1,y):d.error(y)}}else v(-1,"No Transport");return u},param:function(a,c){var e=[],f=function(a,b){b=d.isFunction(b)?b():b,e[e.length]=encodeURIComponent(a)+"="+encodeURIComponent(b)};c===b&&(c=d.ajaxSettings.traditional);if(d.isArray(a)||a.jquery&&!d.isPlainObject(a))d.each(a,function(){f(this.name,this.value)});else for(var g in a)bQ(g,a[g],c,f);return e.join("&").replace(br,"+")}}),d.extend({active:0,lastModified:{},etag:{}});var bT=d.now(),bU=/(\=)\?(&|$)|\?\?/i;d.ajaxSetup({jsonp:"callback",jsonpCallback:function(){return d.expando+"_"+bT++}}),d.ajaxPrefilter("json jsonp",function(b,c,e){var f=typeof b.data==="string";if(b.dataTypes[0]==="jsonp"||c.jsonpCallback||c.jsonp!=null||b.jsonp!==!1&&(bU.test(b.url)||f&&bU.test(b.data))){var g,h=b.jsonpCallback=d.isFunction(b.jsonpCallback)?b.jsonpCallback():b.jsonpCallback,i=a[h],j=b.url,k=b.data,l="$1"+h+"$2",m=function(){a[h]=i,g&&d.isFunction(i)&&a[h](g[0])};b.jsonp!==!1&&(j=j.replace(bU,l),b.url===j&&(f&&(k=k.replace(bU,l)),b.data===k&&(j+=(/\?/.test(j)?"&":"?")+b.jsonp+"="+h))),b.url=j,b.data=k,a[h]=function(a){g=[a]},e.then(m,m),b.converters["script json"]=function(){g||d.error(h+" was not called");return g[0]},b.dataTypes[0]="json";return"script"}}),d.ajaxSetup({accepts:{script:"text/javascript, application/javascript, application/ecmascript, application/x-ecmascript"},contents:{script:/javascript|ecmascript/},converters:{"text script":function(a){d.globalEval(a);return a}}}),d.ajaxPrefilter("script",function(a){a.cache===b&&(a.cache=!1),a.crossDomain&&(a.type="GET",a.global=!1)}),d.ajaxTransport("script",function(a){if(a.crossDomain){var d,e=c.head||c.getElementsByTagName("head")[0]||c.documentElement;return{send:function(f,g){d=c.createElement("script"),d.async="async",a.scriptCharset&&(d.charset=a.scriptCharset),d.src=a.url,d.onload=d.onreadystatechange=function(a,c){if(!d.readyState||/loaded|complete/.test(d.readyState))d.onload=d.onreadystatechange=null,e&&d.parentNode&&e.removeChild(d),d=b,c||g(200,"success")},e.insertBefore(d,e.firstChild)},abort:function(){d&&d.onload(0,1)}}}});var bV=d.now(),bW,bX;d.ajaxSettings.xhr=a.ActiveXObject?function(){return!this.isLocal&&bZ()||b$()}:bZ,bX=d.ajaxSettings.xhr(),d.support.ajax=!!bX,d.support.cors=bX&&"withCredentials"in bX,bX=b,d.support.ajax&&d.ajaxTransport(function(a){if(!a.crossDomain||d.support.cors){var c;return{send:function(e,f){var g=a.xhr(),h,i;a.username?g.open(a.type,a.url,a.async,a.username,a.password):g.open(a.type,a.url,a.async);if(a.xhrFields)for(i in a.xhrFields)g[i]=a.xhrFields[i];a.mimeType&&g.overrideMimeType&&g.overrideMimeType(a.mimeType),!a.crossDomain&&!e["X-Requested-With"]&&(e["X-Requested-With"]="XMLHttpRequest");try{for(i in e)g.setRequestHeader(i,e[i])}catch(j){}g.send(a.hasContent&&a.data||null),c=function(e,i){var j,k,l,m,n;try{if(c&&(i||g.readyState===4)){c=b,h&&(g.onreadystatechange=d.noop,delete bW[h]);if(i)g.readyState!==4&&g.abort();else{j=g.status,l=g.getAllResponseHeaders(),m={},n=g.responseXML,n&&n.documentElement&&(m.xml=n),m.text=g.responseText;try{k=g.statusText}catch(o){k=""}j||!a.isLocal||a.crossDomain?j===1223&&(j=204):j=m.text?200:404}}}catch(p){i||f(-1,p)}m&&f(j,k,m,l)},a.async&&g.readyState!==4?(bW||(bW={},bY()),h=bV++,g.onreadystatechange=bW[h]=c):c()},abort:function(){c&&c(0,1)}}}});var b_={},ca=/^(?:toggle|show|hide)$/,cb=/^([+\-]=)?([\d+.\-]+)([a-z%]*)$/i,cc,cd=[["height","marginTop","marginBottom","paddingTop","paddingBottom"],["width","marginLeft","marginRight","paddingLeft","paddingRight"],["opacity"]];d.fn.extend({show:function(a,b,c){var e,f;if(a||a===0)return this.animate(ce("show",3),a,b,c);for(var g=0,h=this.length;g<h;g++)e=this[g],f=e.style.display,!d._data(e,"olddisplay")&&f==="none"&&(f=e.style.display=""),f===""&&d.css(e,"display")==="none"&&d._data(e,"olddisplay",cf(e.nodeName));for(g=0;g<h;g++){e=this[g],f=e.style.display;if(f===""||f==="none")e.style.display=d._data(e,"olddisplay")||""}return this},hide:function(a,b,c){if(a||a===0)return this.animate(ce("hide",3),a,b,c);for(var e=0,f=this.length;e<f;e++){var g=d.css(this[e],"display");g!=="none"&&!d._data(this[e],"olddisplay")&&d._data(this[e],"olddisplay",g)}for(e=0;e<f;e++)this[e].style.display="none";return this},_toggle:d.fn.toggle,toggle:function(a,b,c){var e=typeof a==="boolean";d.isFunction(a)&&d.isFunction(b)?this._toggle.apply(this,arguments):a==null||e?this.each(function(){var b=e?a:d(this).is(":hidden");d(this)[b?"show":"hide"]()}):this.animate(ce("toggle",3),a,b,c);return this},fadeTo:function(a,b,c,d){return this.filter(":hidden").css("opacity",0).show().end().animate({opacity:b},a,c,d)},animate:function(a,b,c,e){var f=d.speed(b,c,e);if(d.isEmptyObject(a))return this.each(f.complete);return this[f.queue===!1?"each":"queue"](function(){var b=d.extend({},f),c,e=this.nodeType===1,g=e&&d(this).is(":hidden"),h=this;for(c in a){var i=d.camelCase(c);c!==i&&(a[i]=a[c],delete a[c],c=i);if(a[c]==="hide"&&g||a[c]==="show"&&!g)return b.complete.call(this);if(e&&(c==="height"||c==="width")){b.overflow=[this.style.overflow,this.style.overflowX,this.style.overflowY];if(d.css(this,"display")==="inline"&&d.css(this,"float")==="none")if(d.support.inlineBlockNeedsLayout){var j=cf(this.nodeName);j==="inline"?this.style.display="inline-block":(this.style.display="inline",this.style.zoom=1)}else this.style.display="inline-block"}d.isArray(a[c])&&((b.specialEasing=b.specialEasing||{})[c]=a[c][1],a[c]=a[c][0])}b.overflow!=null&&(this.style.overflow="hidden"),b.curAnim=d.extend({},a),d.each(a,function(c,e){var f=new d.fx(h,b,c);if(ca.test(e))f[e==="toggle"?g?"show":"hide":e](a);else{var i=cb.exec(e),j=f.cur();if(i){var k=parseFloat(i[2]),l=i[3]||(d.cssNumber[c]?"":"px");l!=="px"&&(d.style(h,c,(k||1)+l),j=(k||1)/f.cur()*j,d.style(h,c,j+l)),i[1]&&(k=(i[1]==="-="?-1:1)*k+j),f.custom(j,k,l)}else f.custom(j,e,"")}});return!0})},stop:function(a,b){var c=d.timers;a&&this.queue([]),this.each(function(){for(var a=c.length-1;a>=0;a--)c[a].elem===this&&(b&&c[a](!0),c.splice(a,1))}),b||this.dequeue();return this}}),d.each({slideDown:ce("show",1),slideUp:ce("hide",1),slideToggle:ce("toggle",1),fadeIn:{opacity:"show"},fadeOut:{opacity:"hide"},fadeToggle:{opacity:"toggle"}},function(a,b){d.fn[a]=function(a,c,d){return this.animate(b,a,c,d)}}),d.extend({speed:function(a,b,c){var e=a&&typeof a==="object"?d.extend({},a):{complete:c||!c&&b||d.isFunction(a)&&a,duration:a,easing:c&&b||b&&!d.isFunction(b)&&b};e.duration=d.fx.off?0:typeof e.duration==="number"?e.duration:e.duration in d.fx.speeds?d.fx.speeds[e.duration]:d.fx.speeds._default,e.old=e.complete,e.complete=function(){e.queue!==!1&&d(this).dequeue(),d.isFunction(e.old)&&e.old.call(this)};return e},easing:{linear:function(a,b,c,d){return c+d*a},swing:function(a,b,c,d){return(-Math.cos(a*Math.PI)/2+.5)*d+c}},timers:[],fx:function(a,b,c){this.options=b,this.elem=a,this.prop=c,b.orig||(b.orig={})}}),d.fx.prototype={update:function(){this.options.step&&this.options.step.call(this.elem,this.now,this),(d.fx.step[this.prop]||d.fx.step._default)(this)},cur:function(){if(this.elem[this.prop]!=null&&(!this.elem.style||this.elem.style[this.prop]==null))return this.elem[this.prop];var a,b=d.css(this.elem,this.prop);return isNaN(a=parseFloat(b))?!b||b==="auto"?0:b:a},custom:function(a,b,c){function g(a){return e.step(a)}var e=this,f=d.fx;this.startTime=d.now(),this.start=a,this.end=b,this.unit=c||this.unit||(d.cssNumber[this.prop]?"":"px"),this.now=this.start,this.pos=this.state=0,g.elem=this.elem,g()&&d.timers.push(g)&&!cc&&(cc=setInterval(f.tick,f.interval))},show:function(){this.options.orig[this.prop]=d.style(this.elem,this.prop),this.options.show=!0,this.custom(this.prop==="width"||this.prop==="height"?1:0,this.cur()),d(this.elem).show()},hide:function(){this.options.orig[this.prop]=d.style(this.elem,this.prop),this.options.hide=!0,this.custom(this.cur(),0)},step:function(a){var b=d.now(),c=!0;if(a||b>=this.options.duration+this.startTime){this.now=this.end,this.pos=this.state=1,this.update(),this.options.curAnim[this.prop]=!0;for(var e in this.options.curAnim)this.options.curAnim[e]!==!0&&(c=!1);if(c){if(this.options.overflow!=null&&!d.support.shrinkWrapBlocks){var f=this.elem,g=this.options;d.each(["","X","Y"],function(a,b){f.style["overflow"+b]=g.overflow[a]})}this.options.hide&&d(this.elem).hide();if(this.options.hide||this.options.show)for(var h in this.options.curAnim)d.style(this.elem,h,this.options.orig[h]);this.options.complete.call(this.elem)}return!1}var i=b-this.startTime;this.state=i/this.options.duration;var j=this.options.specialEasing&&this.options.specialEasing[this.prop],k=this.options.easing||(d.easing.swing?"swing":"linear");this.pos=d.easing[j||k](this.state,i,0,1,this.options.duration),this.now=this.start+(this.end-this.start)*this.pos,this.update();return!0}},d.extend(d.fx,{tick:function(){var a=d.timers;for(var b=0;b<a.length;b++)a[b]()||a.splice(b--,1);a.length||d.fx.stop()},interval:13,stop:function(){clearInterval(cc),cc=null},speeds:{slow:600,fast:200,_default:400},step:{opacity:function(a){d.style(a.elem,"opacity",a.now)},_default:function(a){a.elem.style&&a.elem.style[a.prop]!=null?a.elem.style[a.prop]=(a.prop==="width"||a.prop==="height"?Math.max(0,a.now):a.now)+a.unit:a.elem[a.prop]=a.now}}}),d.expr&&d.expr.filters&&(d.expr.filters.animated=function(a){return d.grep(d.timers,function(b){return a===b.elem}).length});var cg=/^t(?:able|d|h)$/i,ch=/^(?:body|html)$/i;"getBoundingClientRect"in c.documentElement?d.fn.offset=function(a){var b=this[0],c;if(a)return this.each(function(b){d.offset.setOffset(this,a,b)});if(!b||!b.ownerDocument)return null;if(b===b.ownerDocument.body)return d.offset.bodyOffset(b);try{c=b.getBoundingClientRect()}catch(e){}var f=b.ownerDocument,g=f.documentElement;if(!c||!d.contains(g,b))return c?{top:c.top,left:c.left}:{top:0,left:0};var h=f.body,i=ci(f),j=g.clientTop||h.clientTop||0,k=g.clientLeft||h.clientLeft||0,l=i.pageYOffset||d.support.boxModel&&g.scrollTop||h.scrollTop,m=i.pageXOffset||d.support.boxModel&&g.scrollLeft||h.scrollLeft,n=c.top+l-j,o=c.left+m-k;return{top:n,left:o}}:d.fn.offset=function(a){var b=this[0];if(a)return this.each(function(b){d.offset.setOffset(this,a,b)});if(!b||!b.ownerDocument)return null;if(b===b.ownerDocument.body)return d.offset.bodyOffset(b);d.offset.initialize();var c,e=b.offsetParent,f=b,g=b.ownerDocument,h=g.documentElement,i=g.body,j=g.defaultView,k=j?j.getComputedStyle(b,null):b.currentStyle,l=b.offsetTop,m=b.offsetLeft;while((b=b.parentNode)&&b!==i&&b!==h){if(d.offset.supportsFixedPosition&&k.position==="fixed")break;c=j?j.getComputedStyle(b,null):b.currentStyle,l-=b.scrollTop,m-=b.scrollLeft,b===e&&(l+=b.offsetTop,m+=b.offsetLeft,d.offset.doesNotAddBorder&&(!d.offset.doesAddBorderForTableAndCells||!cg.test(b.nodeName))&&(l+=parseFloat(c.borderTopWidth)||0,m+=parseFloat(c.borderLeftWidth)||0),f=e,e=b.offsetParent),d.offset.subtractsBorderForOverflowNotVisible&&c.overflow!=="visible"&&(l+=parseFloat(c.borderTopWidth)||0,m+=parseFloat(c.borderLeftWidth)||0),k=c}if(k.position==="relative"||k.position==="static")l+=i.offsetTop,m+=i.offsetLeft;d.offset.supportsFixedPosition&&k.position==="fixed"&&(l+=Math.max(h.scrollTop,i.scrollTop),m+=Math.max(h.scrollLeft,i.scrollLeft));return{top:l,left:m}},d.offset={initialize:function(){var a=c.body,b=c.createElement("div"),e,f,g,h,i=parseFloat(d.css(a,"marginTop"))||0,j="<div style='position:absolute;top:0;left:0;margin:0;border:5px solid #000;padding:0;width:1px;height:1px;'><div></div></div><table style='position:absolute;top:0;left:0;margin:0;border:5px solid #000;padding:0;width:1px;height:1px;' cellpadding='0' cellspacing='0'><tr><td></td></tr></table>";d.extend(b.style,{position:"absolute",top:0,left:0,margin:0,border:0,width:"1px",height:"1px",visibility:"hidden"}),b.innerHTML=j,a.insertBefore(b,a.firstChild),e=b.firstChild,f=e.firstChild,h=e.nextSibling.firstChild.firstChild,this.doesNotAddBorder=f.offsetTop!==5,this.doesAddBorderForTableAndCells=h.offsetTop===5,f.style.position="fixed",f.style.top="20px",this.supportsFixedPosition=f.offsetTop===20||f.offsetTop===15,f.style.position=f.style.top="",e.style.overflow="hidden",e.style.position="relative",this.subtractsBorderForOverflowNotVisible=f.offsetTop===-5,this.doesNotIncludeMarginInBodyOffset=a.offsetTop!==i,a.removeChild(b),d.offset.initialize=d.noop},bodyOffset:function(a){var b=a.offsetTop,c=a.offsetLeft;d.offset.initialize(),d.offset.doesNotIncludeMarginInBodyOffset&&(b+=parseFloat(d.css(a,"marginTop"))||0,c+=parseFloat(d.css(a,"marginLeft"))||0);return{top:b,left:c}},setOffset:function(a,b,c){var e=d.css(a,"position");e==="static"&&(a.style.position="relative");var f=d(a),g=f.offset(),h=d.css(a,"top"),i=d.css(a,"left"),j=(e==="absolute"||e==="fixed")&&d.inArray("auto",[h,i])>-1,k={},l={},m,n;j&&(l=f.position()),m=j?l.top:parseInt(h,10)||0,n=j?l.left:parseInt(i,10)||0,d.isFunction(b)&&(b=b.call(a,c,g)),b.top!=null&&(k.top=b.top-g.top+m),b.left!=null&&(k.left=b.left-g.left+n),"using"in b?b.using.call(a,k):f.css(k)}},d.fn.extend({position:function(){if(!this[0])return null;var a=this[0],b=this.offsetParent(),c=this.offset(),e=ch.test(b[0].nodeName)?{top:0,left:0}:b.offset();c.top-=parseFloat(d.css(a,"marginTop"))||0,c.left-=parseFloat(d.css(a,"marginLeft"))||0,e.top+=parseFloat(d.css(b[0],"borderTopWidth"))||0,e.left+=parseFloat(d.css(b[0],"borderLeftWidth"))||0;return{top:c.top-e.top,left:c.left-e.left}},offsetParent:function(){return this.map(function(){var a=this.offsetParent||c.body;while(a&&(!ch.test(a.nodeName)&&d.css(a,"position")==="static"))a=a.offsetParent;return a})}}),d.each(["Left","Top"],function(a,c){var e="scroll"+c;d.fn[e]=function(c){var f=this[0],g;if(!f)return null;if(c!==b)return this.each(function(){g=ci(this),g?g.scrollTo(a?d(g).scrollLeft():c,a?c:d(g).scrollTop()):this[e]=c});g=ci(f);return g?"pageXOffset"in g?g[a?"pageYOffset":"pageXOffset"]:d.support.boxModel&&g.document.documentElement[e]||g.document.body[e]:f[e]}}),d.each(["Height","Width"],function(a,c){var e=c.toLowerCase();d.fn["inner"+c]=function(){return this[0]?parseFloat(d.css(this[0],e,"padding")):null},d.fn["outer"+c]=function(a){return this[0]?parseFloat(d.css(this[0],e,a?"margin":"border")):null},d.fn[e]=function(a){var f=this[0];if(!f)return a==null?null:this;if(d.isFunction(a))return this.each(function(b){var c=d(this);c[e](a.call(this,b,c[e]()))});if(d.isWindow(f)){var g=f.document.documentElement["client"+c];return f.document.compatMode==="CSS1Compat"&&g||f.document.body["client"+c]||g}if(f.nodeType===9)return Math.max(f.documentElement["client"+c],f.body["scroll"+c],f.documentElement["scroll"+c],f.body["offset"+c],f.documentElement["offset"+c]);if(a===b){var h=d.css(f,e),i=parseFloat(h);return d.isNaN(i)?h:i}return this.css(e,typeof a==="string"?a:a+"px")}}),a.jQuery=a.$=d})(window);
;
jQuery.easing={easein:function(x,t,b,c,d){return c*(t/=d)*t+b},easeinout:function(x,t,b,c,d){if(t<d/2)return 2*c*t*t/(d*d)+b;var a=t-d/2;return-2*c*a*a/(d*d)+2*c*a/d+c/2+b},easeout:function(x,t,b,c,d){return-c*t*t/(d*d)+2*c*t/d+b},expoin:function(x,t,b,c,d){var a=1;if(c<0){a*=-1;c*=-1}return a*(Math.exp(Math.log(c)/d*t))+b},expoout:function(x,t,b,c,d){var a=1;if(c<0){a*=-1;c*=-1}return a*(-Math.exp(-Math.log(c)/d*(t-d))+c+1)+b},expoinout:function(x,t,b,c,d){var a=1;if(c<0){a*=-1;c*=-1}if(t<d/2)return a*(Math.exp(Math.log(c/2)/(d/2)*t))+b;return a*(-Math.exp(-2*Math.log(c/2)/d*(t-d))+c+1)+b},bouncein:function(x,t,b,c,d){return c-jQuery.easing['bounceout'](x,d-t,0,c,d)+b},bounceout:function(x,t,b,c,d){if((t/=d)<(1/2.75)){return c*(7.5625*t*t)+b}else if(t<(2/2.75)){return c*(7.5625*(t-=(1.5/2.75))*t+.75)+b}else if(t<(2.5/2.75)){return c*(7.5625*(t-=(2.25/2.75))*t+.9375)+b}else{return c*(7.5625*(t-=(2.625/2.75))*t+.984375)+b}},bounceinout:function(x,t,b,c,d){if(t<d/2)return jQuery.easing['bouncein'](x,t*2,0,c,d)*.5+b;return jQuery.easing['bounceout'](x,t*2-d,0,c,d)*.5+c*.5+b},elasin:function(x,t,b,c,d){var s=1.70158;var p=0;var a=c;if(t==0)return b;if((t/=d)==1)return b+c;if(!p)p=d*.3;if(a<Math.abs(c)){a=c;var s=p/4}else var s=p/(2*Math.PI)*Math.asin(c/a);return-(a*Math.pow(2,10*(t-=1))*Math.sin((t*d-s)*(2*Math.PI)/p))+b},elasout:function(x,t,b,c,d){var s=1.70158;var p=0;var a=c;if(t==0)return b;if((t/=d)==1)return b+c;if(!p)p=d*.3;if(a<Math.abs(c)){a=c;var s=p/4}else var s=p/(2*Math.PI)*Math.asin(c/a);return a*Math.pow(2,-10*t)*Math.sin((t*d-s)*(2*Math.PI)/p)+c+b},elasinout:function(x,t,b,c,d){var s=1.70158;var p=0;var a=c;if(t==0)return b;if((t/=d/2)==2)return b+c;if(!p)p=d*(.3*1.5);if(a<Math.abs(c)){a=c;var s=p/4}else var s=p/(2*Math.PI)*Math.asin(c/a);if(t<1)return-.5*(a*Math.pow(2,10*(t-=1))*Math.sin((t*d-s)*(2*Math.PI)/p))+b;return a*Math.pow(2,-10*(t-=1))*Math.sin((t*d-s)*(2*Math.PI)/p)*.5+c+b},backin:function(x,t,b,c,d){var s=1.70158;return c*(t/=d)*t*((s+1)*t-s)+b},backout:function(x,t,b,c,d){var s=1.70158;return c*((t=t/d-1)*t*((s+1)*t+s)+1)+b},backinout:function(x,t,b,c,d){var s=1.70158;if((t/=d/2)<1)return c/2*(t*t*(((s*=(1.525))+1)*t-s))+b;return c/2*((t-=2)*t*(((s*=(1.525))+1)*t+s)+2)+b},linear:function(x,t,b,c,d){return c*t/d+b}};
;
(function($){$.fn.lavaLamp=function(o){o=$.extend({fx:"linear",speed:500,click:function(){}},o||{});return this.each(function(){var b=$(this),noop=function(){},$back=$('<li class="back"><div class="left"></div></li>').appendTo(b),$li=$("li",this),curr=$("li.current",this)[0]||$($li[0]).addClass("current")[0];$li.not(".back").hover(function(){move(this)},noop);$(this).hover(noop,function(){move(curr)});$li.click(function(e){setCurr(this);return o.click.apply(this,[e,this])});setCurr(curr);function setCurr(a){$back.css({"left":a.offsetLeft+"px","width":a.offsetWidth+"px"});curr=a};function move(a){$back.each(function(){$.dequeue(this,"fx")}).animate({width:a.offsetWidth,left:a.offsetLeft},o.speed,o.fx)}})}})(jQuery);
;
/**
 * jGrowl 1.1.2
 *
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php)
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 *
 * Written by Stan Lemon <stanlemon@mac.com>
 * Last updated: 2008.08.17
 *
 * jGrowl is a jQuery plugin implementing unobtrusive userland notifications.  These 
 * notifications function similarly to the Growl Framework available for
 * Mac OS X (http://growl.info).
 *
 * To Do:
 * - Move library settings to containers and allow them to be changed per container
 *
 * Changes in 1.1.2
 * - Added iPhone styled example
 * - Fixed possible IE7 bug when determining if the ie6 class shoudl be applied.
 * - Added template for the close button, so that it's content could be customized.
 *
 * Changes in 1.1.1
 * - Fixed CSS styling bug for ie6 caused by a mispelling
 * - Changes height restriction on default notifications to min-height
 * - Added skinned examples using a variety of images
 * - Added the ability to customize the content of the [close all] box
 * - Added jTweet, an example of using jGrowl + Twitter
 *
 * Changes in 1.1.0
 * - Multiple container and instances.
 * - Standard $.jGrowl() now wraps $.fn.jGrowl() by first establishing a generic jGrowl container.
 * - Instance methods of a jGrowl container can be called by $.fn.jGrowl(methodName)
 * - Added glue preferenced, which allows notifications to be inserted before or after nodes in the container
 * - Added new log callback which is called before anything is done for the notification
 * - Corner's attribute are now applied on an individual notification basis.
 *
 * Changes in 1.0.4
 * - Various CSS fixes so that jGrowl renders correctly in IE6.
 *
 * Changes in 1.0.3
 * - Fixed bug with options persisting across notifications
 * - Fixed theme application bug
 * - Simplified some selectors and manipulations.
 * - Added beforeOpen and beforeClose callbacks
 * - Reorganized some lines of code to be more readable
 * - Removed unnecessary this.defaults context
 * - If corners plugin is present, it's now customizable.
 * - Customizable open animation.
 * - Customizable close animation.
 * - Customizable animation easing.
 * - Added customizable positioning (top-left, top-right, bottom-left, bottom-right, center)
 *
 * Changes in 1.0.2
 * - All CSS styling is now external.
 * - Added a theme parameter which specifies a secondary class for styling, such
 *   that notifications can be customized in appearance on a per message basis.
 * - Notification life span is now customizable on a per message basis.
 * - Added the ability to disable the global closer, enabled by default.
 * - Added callbacks for when a notification is opened or closed.
 * - Added callback for the global closer.
 * - Customizable animation speed.
 * - jGrowl now set itself up and tears itself down.
 *
 * Changes in 1.0.1:
 * - Removed dependency on metadata plugin in favor of .data()
 * - Namespaced all events
 */
(function($) {

    /** jGrowl Wrapper - Establish a base jGrowl Container for compatibility with older releases. **/
    $.jGrowl = function( m , o ) {
        // To maintain compatibility with older version that only supported one instance we'll create the base container.
        if ( $('#jGrowl').size() == 0 ) $('<div id="jGrowl"></div>').addClass($.jGrowl.defaults.position).appendTo('body');
        // Create a notification on the container.
        $('#jGrowl').jGrowl(m,o);
    };


    /** Raise jGrowl Notification on a jGrowl Container **/
    $.fn.jGrowl = function( m , o ) {
        if ( $.isFunction(this.each) ) {
            var args = arguments;

            return this.each(function() {
                var self = this;

                /** Create a jGrowl Instance on the Container if it does not exist **/
                if ( $(this).data('jGrowl.instance') == undefined ) {
                    $(this).data('jGrowl.instance', new $.fn.jGrowl());
                    $(this).data('jGrowl.instance').startup( this );
                }

                /** Optionally call jGrowl instance methods, or just raise a normal notification **/
                if ( $.isFunction($(this).data('jGrowl.instance')[m]) ) {
                    $(this).data('jGrowl.instance')[m].apply( $(this).data('jGrowl.instance') , $.makeArray(args).slice(1) );
                } else {
                    $(this).data('jGrowl.instance').notification( m , o );
                }
            });
        };
    };

    $.extend( $.fn.jGrowl.prototype , {

        /** Default JGrowl Settings **/
        defaults: {
            header:         '',
            sticky:         false,
            position:       'bottom-right', // Is this still needed?
            glue:           'after',
            theme:          'default',
            corners:        '10px',
            check:          500,
            life:           3000,
            speed:          'normal',
            easing:         '',
            closer:         true,
            closeTemplate: '&times;',
            closerTemplate: '<div>[ close all ]</div>',
            log:            function(e,m,o) {},
            beforeOpen:     function(e,m,o) {},
            open:           function(e,m,o) {},
            beforeClose:    function(e,m,o) {},
            close:          function(e,m,o) {},
            animateOpen:    {
                opacity:    'show'
            },
            animateClose:   {
                opacity:    'hide'
            }
        },
        
        /** jGrowl Container Node **/
        element:    null,
    
        /** Interval Function **/
        interval:   null,
        
        /** Create a Notification **/
        notification:   function( message , o ) {
            var self = this;
            var o = $.extend({}, this.defaults, o);

            o.log.apply( this.element , [this.element,message,o] );

            var notification = $('<div class="jGrowl-notification"><div class="close">' + o.closeTemplate + '</div><div class="header">' + o.header + '</div><div class="message">' + message + '</div></div>')
                .data("jGrowl", o).addClass(o.theme).children('div.close').bind("click.jGrowl", function() {
                    $(this).unbind('click.jGrowl').parent().trigger('jGrowl.beforeClose').animate(o.animateClose, o.speed, o.easing, function() {
                        $(this).trigger('jGrowl.close').remove();
                    });
                }).parent();
                
            ( o.glue == 'after' ) ? $('div.jGrowl-notification:last', this.element).after(notification) : $('div.jGrowl-notification:first', this.element).before(notification);

            /** Notification Actions **/
            $(notification).bind("mouseover.jGrowl", function() {
                $(this).data("jGrowl").pause = true;
            }).bind("mouseout.jGrowl", function() {
                $(this).data("jGrowl").pause = false;
            }).bind('jGrowl.beforeOpen', function() {
                o.beforeOpen.apply( self.element , [self.element,message,o] );
            }).bind('jGrowl.open', function() {
                o.open.apply( self.element , [self.element,message,o] );
            }).bind('jGrowl.beforeClose', function() {
                o.beforeClose.apply( self.element , [self.element,message,o] );
            }).bind('jGrowl.close', function() {
                o.close.apply( self.element , [self.element,message,o] );
            }).trigger('jGrowl.beforeOpen').animate(o.animateOpen, o.speed, o.easing, function() {
                $(this).data("jGrowl").created = new Date();
            }).trigger('jGrowl.open');
        
            /** Optional Corners Plugin **/
            if ( $.fn.corner != undefined ) $(notification).corner( o.corners );

            /** Add a Global Closer if more than one notification exists **/
            if ( $('div.jGrowl-notification:parent', this.element).size() > 1 && $('div.jGrowl-closer', this.element).size() == 0 && this.defaults.closer != false ) {
                $(this.defaults.closerTemplate).addClass('jGrowl-closer').addClass(this.defaults.theme).appendTo(this.element).animate(this.defaults.animateOpen, this.defaults.speed, this.defaults.easing).bind("click.jGrowl", function() {
                    $(this).siblings().children('div.close').trigger("click.jGrowl");

                    if ( $.isFunction( self.defaults.closer ) ) self.defaults.closer.apply( $(this).parent()[0] , [$(this).parent()[0]] );
                });
            };
        },

        /** Update the jGrowl Container, removing old jGrowl notifications **/
        update:  function() {
            $(this.element).find('div.jGrowl-notification:parent').each( function() {
                if ( $(this).data("jGrowl") != undefined && $(this).data("jGrowl").created != undefined && ($(this).data("jGrowl").created.getTime() + $(this).data("jGrowl").life)  < (new Date()).getTime() && $(this).data("jGrowl").sticky != true && 
                     ($(this).data("jGrowl").pause == undefined || $(this).data("jGrowl").pause != true) ) {
                    $(this).children('div.close').trigger('click.jGrowl');
                }
            });

            if ( $(this.element).find('div.jGrowl-notification:parent').size() < 2 ) {
                $(this.element).find('div.jGrowl-closer').animate(this.defaults.animateClose, this.defaults.speed, this.defaults.easing, function() {
                    $(this).remove();
                });
            };
        },

        /** Setup the jGrowl Notification Container **/
        startup:    function(e) {
            this.element = $(e).addClass('jGrowl').append('<div class="jGrowl-notification"></div>');
            this.interval = setInterval( function() { jQuery(e).data('jGrowl.instance').update(); }, this.defaults.check);
            
            if ($.browser.msie && parseInt($.browser.version) < 7 && !window["XMLHttpRequest"]) $(this.element).addClass('ie6');
        },

        /** Shutdown jGrowl, removing it and clearing the interval **/
        shutdown:   function() {
            $(this.element).removeClass('jGrowl').find('div.jGrowl-notification').remove();
            clearInterval( this.interval );
        }
    });
    
    /** Reference the Defaults Object for compatibility with older versions of jGrowl **/
    $.jGrowl.defaults = $.fn.jGrowl.prototype.defaults;

})(jQuery);
;
/*
 * Facebox (for jQuery)
 * version: 1.2 (05/05/2008)
 * @requires jQuery v1.2 or later
 *
 * Examples at http://famspam.com/facebox/
 *
 * Licensed under the MIT:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 * Copyright 2007, 2008 Chris Wanstrath [ chris@ozmm.org ]
 *
 * Usage:
 *
 *  jQuery(document).ready(function() {
 *    jQuery('a[rel*=facebox]').facebox()
 *  })
 *
 *  <a href="#terms" rel="facebox">Terms</a>
 *    Loads the #terms div in the box
 *
 *  <a href="terms.html" rel="facebox">Terms</a>
 *    Loads the terms.html page in the box
 *
 *  <a href="terms.png" rel="facebox">Terms</a>
 *    Loads the terms.png image in the box
 *
 *
 *  You can also use it programmatically:
 *
 *    jQuery.facebox('some html')
 *    jQuery.facebox('some html', 'my-groovy-style')
 *
 *  The above will open a facebox with "some html" as the content.
 *
 *    jQuery.facebox(function($) {
 *      $.get('blah.html', function(data) { $.facebox(data) })
 *    })
 *
 *  The above will show a loading screen before the passed function is called,
 *  allowing for a better ajaxy experience.
 *
 *  The facebox function can also display an ajax page, an image, or the contents of a div:
 *
 *    jQuery.facebox({ ajax: 'remote.html' })
 *    jQuery.facebox({ ajax: 'remote.html' }, 'my-groovy-style')
 *    jQuery.facebox({ image: 'stairs.jpg' })
 *    jQuery.facebox({ image: 'stairs.jpg' }, 'my-groovy-style')
 *    jQuery.facebox({ div: '#box' })
 *    jQuery.facebox({ div: '#box' }, 'my-groovy-style')
 *
 *  Want to close the facebox?  Trigger the 'close.facebox' document event:
 *
 *    jQuery(document).trigger('close.facebox')
 *
 *  Facebox also has a bunch of other hooks:
 *
 *    loading.facebox
 *    beforeReveal.facebox
 *    reveal.facebox (aliased as 'afterReveal.facebox')
 *    init.facebox
 *    afterClose.facebox
 *
 *  Simply bind a function to any of these hooks:
 *
 *   $(document).bind('reveal.facebox', function() { ...stuff to do after the facebox and contents are revealed... })
 *
 */
(function($) {
  $.facebox = function(data, klass) {
    $.facebox.loading()

    if (data.ajax) fillFaceboxFromAjax(data.ajax, klass)
    else if (data.image) fillFaceboxFromImage(data.image, klass)
    else if (data.div) fillFaceboxFromHref(data.div, klass)
    else if ($.isFunction(data)) data.call($)
    else $.facebox.reveal(data, klass)
  }

  /*
   * Public, $.facebox methods
   */

  $.extend($.facebox, {
    settings: {
      opacity      : 0.2,
      overlay      : true,
      loadingImage  : 'http://stat.codeforces.ru/images/facebox/loading.gif',
      closeImage    : 'http://stat.codeforces.ru/images/facebox/closelabel.png',
      imageTypes   : [ 'png', 'jpg', 'jpeg', 'gif' ],
      faceboxHtml  : '\
    <div id="facebox" style="display:none;"> \
      <div class="popup"> \
        <div class="content"> \
        </div> \
        <a href="#" class="close"><img src="http://stat.codeforces.ru/images/facebox/closelabel.png" title="close" class="close_image" /></a> \
      </div> \
    </div>'
    },

    loading: function() {
      init()
      if ($('#facebox .loading').length == 1) return true
      showOverlay()

      $('#facebox .content').empty()
      $('#facebox .body').children().hide().end().
        append('<div class="loading"><img src="'+$.facebox.settings.loadingImage+'"/></div>')

      $('#facebox').css({
        top:	getPageScroll()[1] + (getPageHeight() / 10),
        left:	$(window).width() / 2 - 205
      }).show()

      $(document).bind('keydown.facebox', function(e) {
        if (e.keyCode == 27) $.facebox.close()
        return true
      })
      $(document).trigger('loading.facebox')
    },

    reveal: function(data, klass) {
      $(document).trigger('beforeReveal.facebox')
      if (klass) $('#facebox .content').addClass(klass)
      $('#facebox .content').append(data)
      $('#facebox .loading').remove()
      $('#facebox .body').children().fadeIn('normal')
      $('#facebox').css('left', $(window).width() / 2 - ($('#facebox .popup').width() / 2))
      $(document).trigger('reveal.facebox').trigger('afterReveal.facebox')
    },

    close: function() {
      $(document).trigger('close.facebox')
      return false
    }
  })

  /*
   * Public, $.fn methods
   */

  $.fn.facebox = function(settings) {
    if ($(this).length == 0) return

    init(settings)

    function clickHandler() {
      $.facebox.loading(true)

      // support for rel="facebox.inline_popup" syntax, to add a class
      // also supports deprecated "facebox[.inline_popup]" syntax
      var klass = this.rel.match(/facebox\[?\.(\w+)\]?/)
      if (klass) klass = klass[1]

      fillFaceboxFromHref(this.href, klass)
      return false
    }

    return this.bind('click.facebox', clickHandler)
  }

  /*
   * Private methods
   */

  // called one time to setup facebox on this page
  function init(settings) {
    if ($.facebox.settings.inited) return true
    else $.facebox.settings.inited = true

    $(document).trigger('init.facebox')
    makeCompatible()

    var imageTypes = $.facebox.settings.imageTypes.join('|')
    $.facebox.settings.imageTypesRegexp = new RegExp('\.(' + imageTypes + ')$', 'i')

    if (settings) $.extend($.facebox.settings, settings)
    $('body').append($.facebox.settings.faceboxHtml)

    var preload = [ new Image(), new Image() ]
    preload[0].src = $.facebox.settings.closeImage
    preload[1].src = $.facebox.settings.loadingImage

    $('#facebox').find('.b:first, .bl').each(function() {
      preload.push(new Image())
      preload.slice(-1).src = $(this).css('background-image').replace(/url\((.+)\)/, '$1')
    })

    $('#facebox .close').click($.facebox.close)
    $('#facebox .close_image').attr('src', $.facebox.settings.closeImage)
  }

  // getPageScroll() by quirksmode.com
  function getPageScroll() {
    var xScroll, yScroll;
    if (self.pageYOffset) {
      yScroll = self.pageYOffset;
      xScroll = self.pageXOffset;
    } else if (document.documentElement && document.documentElement.scrollTop) {	 // Explorer 6 Strict
      yScroll = document.documentElement.scrollTop;
      xScroll = document.documentElement.scrollLeft;
    } else if (document.body) {// all other Explorers
      yScroll = document.body.scrollTop;
      xScroll = document.body.scrollLeft;
    }
    return new Array(xScroll,yScroll)
  }

  // Adapted from getPageSize() by quirksmode.com
  function getPageHeight() {
    var windowHeight
    if (self.innerHeight) {	// all except Explorer
      windowHeight = self.innerHeight;
    } else if (document.documentElement && document.documentElement.clientHeight) { // Explorer 6 Strict Mode
      windowHeight = document.documentElement.clientHeight;
    } else if (document.body) { // other Explorers
      windowHeight = document.body.clientHeight;
    }
    return windowHeight
  }

  // Backwards compatibility
  function makeCompatible() {
    var $s = $.facebox.settings

    $s.loadingImage = $s.loading_image || $s.loadingImage
    $s.closeImage = $s.close_image || $s.closeImage
    $s.imageTypes = $s.image_types || $s.imageTypes
    $s.faceboxHtml = $s.facebox_html || $s.faceboxHtml
  }

  // Figures out what you want to display and displays it
  // formats are:
  //     div: #id
  //   image: blah.extension
  //    ajax: anything else
  function fillFaceboxFromHref(href, klass) {
    // div
    if (href.match(/#/)) {
      var url    = window.location.href.split('#')[0]
      var target = href.replace(url,'')
      if (target == '#') return
      $.facebox.reveal($(target).html(), klass)

    // image
    } else if (href.match($.facebox.settings.imageTypesRegexp)) {
      fillFaceboxFromImage(href, klass)
    // ajax
    } else {
      fillFaceboxFromAjax(href, klass)
    }
  }

  function fillFaceboxFromImage(href, klass) {
    var image = new Image()
    image.onload = function() {
      $.facebox.reveal('<div class="image"><img src="' + image.src + '" /></div>', klass)
    }
    image.src = href
  }

  function fillFaceboxFromAjax(href, klass) {
    $.get(href, function(data) { $.facebox.reveal(data, klass) })
  }

  function skipOverlay() {
    return $.facebox.settings.overlay == false || $.facebox.settings.opacity === null
  }

  function showOverlay() {
    if (skipOverlay()) return

    if ($('#facebox_overlay').length == 0)
      $("body").append('<div id="facebox_overlay" class="facebox_hide"></div>')

    $('#facebox_overlay').hide().addClass("facebox_overlayBG")
      .css('opacity', $.facebox.settings.opacity)
      .click(function() { $(document).trigger('close.facebox') })
      .fadeIn(200)
    return false
  }

  function hideOverlay() {
    if (skipOverlay()) return

    $('#facebox_overlay').fadeOut(200, function(){
      $("#facebox_overlay").removeClass("facebox_overlayBG")
      $("#facebox_overlay").addClass("facebox_hide")
      $("#facebox_overlay").remove()
    })

    return false
  }

  /*
   * Bindings
   */

  $(document).bind('close.facebox', function() {
    $(document).unbind('keydown.facebox')
    $('#facebox').fadeOut(function() {
      $('#facebox .content').removeClass().addClass('content')
      $('#facebox .loading').remove()
      $(document).trigger('afterClose.facebox')
    })
    hideOverlay()
  })

})(jQuery);

;
/**
 * WYSIWYG - jQuery plugin 0.96
 * (Pretty girl)
 *
 * Copyright (c) 2008-2009 Juan M Martinez, 2010-2011 Akzhan Abdulin and all contributors
 * https://github.com/akzhan/jwysiwyg
 *
 * Dual licensed under the MIT and GPL licenses:
 *   http://www.opensource.org/licenses/mit-license.php
 *   http://www.gnu.org/licenses/gpl.html
 *
 */

/*jslint browser: true, forin: true */

(function ($) {
	/* Wysiwyg namespace: private properties and methods */

	var console = window.console ? window.console : {
		log: $.noop,
		error: function (msg) {
			$.error(msg);
		}
	};

	function Wysiwyg() {
		this.controls = {
			bold: {
				groupIndex: 0,
				visible: true,
				tags: ["b", "strong"],
				css: {
					fontWeight: "bold"
				},
				tooltip: "Bold",
				hotkey: {"ctrl": 1, "key": 66}
			},

			copy: {
				groupIndex: 8,
				visible: false,
				tooltip: "Copy"
			},

			createLink: {
				groupIndex: 6,
				visible: true,
				exec: function () {
					var self = this;
					if ($.wysiwyg.controls && $.wysiwyg.controls.link) {
						$.wysiwyg.controls.link.init(this);
					} else if ($.wysiwyg.autoload) {
						$.wysiwyg.autoload.control("wysiwyg.link.js", function () {
							self.controls.createLink.exec.apply(self);
						});
					} else {
						console.error("$.wysiwyg.controls.link not defined. You need to include wysiwyg.link.js file");
					}
				},
				tags: ["a"],
				tooltip: "Create link"
			},

			cut: {
				groupIndex: 8,
				visible: false,
				tooltip: "Cut"
			},

			decreaseFontSize: {
				groupIndex: 9,
				visible: false && !($.browser.msie),
				tags: ["small"],
				tooltip: "Decrease font size",
				exec: function () {
					this.decreaseFontSize();
				}
			},

			h1: {
				groupIndex: 7,
				visible: true,
				className: "h1",
				command: ($.browser.msie || $.browser.safari) ? "FormatBlock" : "heading",
				"arguments": ($.browser.msie || $.browser.safari) ? "<h1>" : "h1",
				tags: ["h1"],
				tooltip: "Header 1"
			},

			h2: {
				groupIndex: 7,
				visible: true,
				className: "h2",
				command: ($.browser.msie || $.browser.safari)	? "FormatBlock" : "heading",
				"arguments": ($.browser.msie || $.browser.safari) ? "<h2>" : "h2",
				tags: ["h2"],
				tooltip: "Header 2"
			},

			h3: {
				groupIndex: 7,
				visible: true,
				className: "h3",
				command: ($.browser.msie || $.browser.safari) ? "FormatBlock" : "heading",
				"arguments": ($.browser.msie || $.browser.safari) ? "<h3>" : "h3",
				tags: ["h3"],
				tooltip: "Header 3"
			},

			highlight: {
				tooltip:     "Highlight",
				className:   "highlight",
				groupIndex:  1,
				visible:     false,
				css: {
					backgroundColor: "rgb(255, 255, 102)"
				},
				exec: function () {
					var command, node, selection, args;

					if ($.browser.msie || $.browser.safari) {
						command = "backcolor";
					} else {
						command = "hilitecolor";
					}

					if ($.browser.msie) {
						node = this.getInternalRange().parentElement();
					} else {
						selection = this.getInternalSelection();
						node = selection.extentNode || selection.focusNode;

						while (node.style === undefined) {
							node = node.parentNode;
							if (node.tagName && node.tagName.toLowerCase() === "body") {
								return;
							}
						}
					}

					if (node.style.backgroundColor === "rgb(255, 255, 102)" ||
							node.style.backgroundColor === "#ffff66") {
						args = "#ffffff";
					} else {
						args = "#ffff66";
					}

					this.editorDoc.execCommand(command, false, args);
				}
			},

			html: {
				groupIndex: 10,
				visible: false,
				exec: function () {
					var elementHeight;

					if (this.options.resizeOptions && $.fn.resizable) {
						elementHeight = this.element.height();
					}

					if (this.viewHTML) {
						this.setContent($(this.original).val());
						$(this.original).hide();
						this.editor.show();

						if (this.options.resizeOptions && $.fn.resizable) {
							// if element.height still the same after frame was shown
							if (elementHeight === this.element.height()) {
								this.element.height(elementHeight + this.editor.height());
							}

							this.element.resizable($.extend(true, {
								alsoResize: this.editor
							}, this.options.resizeOptions));
						}
						
						this.ui.toolbar.find("li").each(function () {
							var li = $(this);

							if (li.hasClass("html")) {
								li.removeClass("active");
							} else {
								li.attr("disabled", "false");
							}
						});
					} else {
						this.saveContent();
						$(this.original).css({
							width:	this.element.outerWidth() - 6,
							height: this.element.height() - this.ui.toolbar.height() - 6,
							resize: "none"
						}).show();
						this.editor.hide();
						
						if (this.options.resizeOptions && $.fn.resizable) {
							// if element.height still the same after frame was hidden
							if (elementHeight === this.element.height()) {
								this.element.height(this.ui.toolbar.height());
							}

							this.element.resizable("destroy");
						}

						this.ui.toolbar.find("li").each(function () {
							var li = $(this);

							if (li.hasClass("html")) {
								li.addClass("active");
							} else {
								if (false === li.hasClass("fullscreen")) {
									li.removeClass("active");
									li.attr("disabled", "true");
								}
							}
						});
					}

					this.viewHTML = !(this.viewHTML);
				},
				tooltip: "View source code"
			},

			increaseFontSize: {
				groupIndex: 9,
				visible: false && !($.browser.msie),
				tags: ["big"],
				tooltip: "Increase font size",
				exec: function () {
					this.increaseFontSize();
				}
			},

			indent: {
				groupIndex: 2,
				visible: true,
				tooltip: "Indent"
			},

			insertHorizontalRule: {
				groupIndex: 6,
				visible: true,
				tags: ["hr"],
				tooltip: "Insert Horizontal Rule"
			},

			insertImage: {
				groupIndex: 6,
				visible: true,
				exec: function () {
					var self = this;

					if ($.wysiwyg.controls && $.wysiwyg.controls.image) {
						$.wysiwyg.controls.image.init(this);
					} else if ($.wysiwyg.autoload) {
						$.wysiwyg.autoload.control("wysiwyg.image.js", function () {
							self.controls.insertImage.exec.apply(self);
						});
					} else {
						console.error("$.wysiwyg.controls.image not defined. You need to include wysiwyg.image.js file");
					}
				},
				tags: ["img"],
				tooltip: "Insert image"
			},

			insertOrderedList: {
				groupIndex: 5,
				visible: true,
				tags: ["ol"],
				tooltip: "Insert Ordered List"
			},

			insertTable: {
				groupIndex: 6,
				visible: true,
				exec: function () {
					var self = this;

					if ($.wysiwyg.controls && $.wysiwyg.controls.table) {
						$.wysiwyg.controls.table(this);
					} else if ($.wysiwyg.autoload) {
						$.wysiwyg.autoload.control("wysiwyg.table.js", function () {
							self.controls.insertTable.exec.apply(self);
						});
					} else {
						console.error("$.wysiwyg.controls.table not defined. You need to include wysiwyg.table.js file");
					}
				},
				tags: ["table"],
				tooltip: "Insert table"
			},

			insertUnorderedList: {
				groupIndex: 5,
				visible: true,
				tags: ["ul"],
				tooltip: "Insert Unordered List"
			},

			italic: {
				groupIndex: 0,
				visible: true,
				tags: ["i", "em"],
				css: {
					fontStyle: "italic"
				},
				tooltip: "Italic",
				hotkey: {"ctrl": 1, "key": 73}
			},

			justifyCenter: {
				groupIndex: 1,
				visible: true,
				tags: ["center"],
				css: {
					textAlign: "center"
				},
				tooltip: "Justify Center"
			},

			justifyFull: {
				groupIndex: 1,
				visible: true,
				css: {
					textAlign: "justify"
				},
				tooltip: "Justify Full"
			},

			justifyLeft: {
				visible: true,
				groupIndex: 1,
				css: {
					textAlign: "left"
				},
				tooltip: "Justify Left"
			},

			justifyRight: {
				groupIndex: 1,
				visible: true,
				css: {
					textAlign: "right"
				},
				tooltip: "Justify Right"
			},

			ltr: {
				groupIndex: 10,
				visible: false,
				exec: function () {
					var range = this.getInternalRange(),
						p = this.dom.getElement("p");

					if (!p) {
						return false;
					}

					$(p).attr("dir", "ltr");
				},
				tooltip : "Left to Right"
			},

			outdent: {
				groupIndex: 2,
				visible: true,
				tooltip: "Outdent"
			},

			paragraph: {
				groupIndex: 7,
				visible: false,
				className: "paragraph",
				command: "FormatBlock",
				"arguments": ($.browser.msie || $.browser.safari) ? "<p>" : "p",
				tags: ["p"],
				tooltip: "Paragraph"
			},

			paste: {
				groupIndex: 8,
				visible: false,
				tooltip: "Paste"
			},

			redo: {
				groupIndex: 4,
				visible: true,
				tooltip: "Redo"
			},

			removeFormat: {
				groupIndex: 10,
				visible: true,
				exec: function () {
					this.removeFormat();
				},
				tooltip: "Remove formatting"
			},

			rtl: {
				groupIndex: 10,
				visible: false,
				exec: function () {
					var range = this.getInternalRange(),
						p = this.dom.getElement("p");

					if (!p) {
						return false;
					}

					$(p).attr("dir", "rtl");
				},
				tooltip : "Right to Left"
			},

			strikeThrough: {
				groupIndex: 0,
				visible: true,
				tags: ["s", "strike"],
				css: {
					textDecoration: "line-through"
				},
				tooltip: "Strike-through"
			},

			subscript: {
				groupIndex: 3,
				visible: true,
				tags: ["sub"],
				tooltip: "Subscript"
			},

			superscript: {
				groupIndex: 3,
				visible: true,
				tags: ["sup"],
				tooltip: "Superscript"
			},

			underline: {
				groupIndex: 0,
				visible: true,
				tags: ["u"],
				css: {
					textDecoration: "underline"
				},
				tooltip: "Underline",
				hotkey: {"ctrl": 1, "key": 85}
			},

			undo: {
				groupIndex: 4,
				visible: true,
				tooltip: "Undo"
			}
		};

		this.defaults = {
			html: '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"><html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"></head><body style="margin: 0px;">INITIAL_CONTENT</body></html>',
			debug: false,
			controls: {},
			css: {},
			events: {},
			autoGrow: false,
			autoSave: true,
			brIE: true,					// http://code.google.com/p/jwysiwyg/issues/detail?id=15
			formHeight: 270,
			formWidth: 440,
			iFrameClass: null,
			initialContent: "",
			maxHeight: 10000,			// see autoGrow
			maxLength: 0,
			messages: {
				nonSelection: "Select the text you wish to link"
			},
			toolbarHtml: '<ul role="menu" class="toolbar"></ul>',
			removeHeadings: false,
			replaceDivWithP: false,
			resizeOptions: false,
			rmUnusedControls: false,	// https://github.com/akzhan/jwysiwyg/issues/52
			rmUnwantedBr: true,			// http://code.google.com/p/jwysiwyg/issues/detail?id=11
			tableFiller: "&nbsp;",
			initialMinHeight: null,

			controlImage: {
				forceRelativeUrls: false
			},

			controlLink: {
				forceRelativeUrls: false
			},

			plugins: { // placeholder for plugins settings
				autoload: false,
				i18n: false,
				rmFormat: {
					rmMsWordMarkup: false
				}
			}
		};

		this.availableControlProperties = [
			"arguments",
			"callback",
			"className",
			"command",
			"css",
			"custom",
			"exec",
			"groupIndex",
			"hotkey",
			"icon",
			"tags",
			"tooltip",
			"visible"
		];

		this.editor			= null;
		this.editorDoc		= null;
		this.element		= null;
		this.options		= {};
		this.original		= null;
		this.savedRange		= null;
		this.timers			= [];
		this.validKeyCodes	= [8, 9, 13, 16, 17, 18, 19, 20, 27, 33, 34, 35, 36, 37, 38, 39, 40, 45, 46];

		this.isDestroyed	= false;

		this.dom		= { // DOM related properties and methods
			ie:		{
				parent: null // link to dom
			},
			w3c:	{
				parent: null // link to dom
			}
		};
		this.dom.parent		= this;
		this.dom.ie.parent	= this.dom;
		this.dom.w3c.parent	= this.dom;

		this.ui			= {};	// UI related properties and methods
		this.ui.self	= this;
		this.ui.toolbar	= null;
		this.ui.initialHeight = null; // ui.grow

		this.dom.getAncestor = function (element, filterTagName) {
			filterTagName = filterTagName.toLowerCase();

			while (element && "body" !== element.tagName.toLowerCase()) {
				if (filterTagName === element.tagName.toLowerCase()) {
					return element;
				}

				element = element.parentNode;
			}

			return null;
		};

		this.dom.getElement = function (filterTagName) {
			var dom = this;

			if (window.getSelection) {
				return dom.w3c.getElement(filterTagName);
			} else {
				return dom.ie.getElement(filterTagName);
			}
		};

		this.dom.ie.getElement = function (filterTagName) {
			var dom			= this.parent,
				selection	= dom.parent.getInternalSelection(),
				range		= selection.createRange(),
				element;

			if ("Control" === selection.type) {
				// control selection
				if (1 === range.length) {
					element = range.item(0);
				} else {
					// multiple control selection
					return null;
				}
			} else {
				element = range.parentElement();
			}

			return dom.getAncestor(element, filterTagName);
		};

		this.dom.w3c.getElement = function (filterTagName) {
			var dom		= this.parent,
				range	= dom.parent.getInternalRange(),
				element;

			if (!range) {
				return null;
			}

			element	= range.commonAncestorContainer;

			if (3 === element.nodeType) {
				element = element.parentNode;
			}

			// if startContainer not Text, Comment, or CDATASection element then
			// startOffset is the number of child nodes between the start of the
			// startContainer and the boundary point of the Range
			if (element === range.startContainer) {
				element = element.childNodes[range.startOffset];
			}

			return dom.getAncestor(element, filterTagName);
		};

		this.ui.addHoverClass = function () {
			$(this).addClass("wysiwyg-button-hover");
		};

		this.ui.appendControls = function () {
			var ui = this,
				self = this.self,
				controls = self.parseControls(),
				hasVisibleControls	= true, // to prevent separator before first item
				groups = [],
				controlsByGroup = {},
				i,
				currentGroupIndex, // jslint wants all vars at top of function
				iterateGroup = function (controlName, control) {
					if (control.groupIndex && currentGroupIndex !== control.groupIndex) {
						currentGroupIndex = control.groupIndex;
						hasVisibleControls = false;
					}

					if (!control.visible) {
						return;
					}

					if (!hasVisibleControls) {
						ui.appendItemSeparator();
						hasVisibleControls = true;
					}

					if (control.custom) {
						ui.appendItemCustom(controlName, control);
					} else {
						ui.appendItem(controlName, control);
					}
				};

			$.each(controls, function (name, c) {
				var index = "empty";

				if (undefined !== c.groupIndex) {
					if ("" === c.groupIndex) {
						index = "empty";
					} else {
						index = c.groupIndex;
					}
				}

				if (undefined === controlsByGroup[index]) {
					groups.push(index);
					controlsByGroup[index] = {};
				}
				controlsByGroup[index][name] = c;
			});

			groups.sort(function (a, b) {
				if ("number" === typeof (a) && typeof (a) === typeof (b)) {
					return (a - b);
				} else {
					a = "" + a;
					b = "" + b;

					if (a > b) {
						return 1;
					}

					if (a === b) {
						return 0;
					}

					return -1;
				}
			});

			if (0 < groups.length) {
				// set to first index in groups to proper placement of separator
				currentGroupIndex = groups[0];
			}

			for (i = 0; i < groups.length; i += 1) {
				$.each(controlsByGroup[groups[i]], iterateGroup);
			}
		};

		this.ui.appendItem = function (name, control) {
			var self = this.self,
				className = control.className || control.command || name || "empty",
				tooltip = control.tooltip || control.command || name || "";

			return $('<li role="menuitem" unselectable="on">' + (className) + "</li>")
				.addClass(className)
				.attr("title", tooltip)
				.hover(this.addHoverClass, this.removeHoverClass)
				.click(function () {
					if ("true" === $(this).attr("disabled")) {
						return false;
					}

					self.triggerControl.apply(self, [name, control]);

					this.blur();
					self.ui.returnRange();
					self.ui.focus();
				})
				.appendTo(self.ui.toolbar);
		};

		this.ui.appendItemCustom = function (name, control) {
			var self = this.self,
				tooltip = control.tooltip || control.command || name || "";

			if (control.callback) {
				$(window).bind("trigger-" + name + ".wysiwyg", control.callback);
			}

			return $('<li role="menuitem" unselectable="on" style="background: url(\'' + control.icon + '\') no-repeat;"></li>')
				.addClass("custom-command-" + name)
				.addClass("wysiwyg-custom-command")
				.addClass(name)
				.attr("title", control.tooltip)
				.hover(this.addHoverClass, this.removeHoverClass)
				.click(function () {
					if ("true" === $(this).attr("disabled")) {
						return false;
					}

					self.triggerControl.apply(self, [name, control]);

					this.blur();
					self.ui.returnRange();
					self.ui.focus();

					self.triggerControlCallback(name);
				})
				.appendTo(self.ui.toolbar);
		};

		this.ui.appendItemSeparator = function () {
			var self = this.self;
			return $('<li role="separator" class="separator"></li>').appendTo(self.ui.toolbar);
		};

		this.autoSaveFunction = function () {
			this.saveContent();
		};

		this.ui.checkTargets = function (element) {
			var self = this.self;

			$.each(self.options.controls, function (name, control) {
				var className = control.className || control.command || name || "empty",
					tags,
					elm,
					css,
					el,
					checkActiveStatus = function (cssProperty, cssValue) {
						var handler;

						if ("function" === typeof (cssValue)) {
							handler = cssValue;
							if (handler(el.css(cssProperty).toString().toLowerCase(), self)) {
								self.ui.toolbar.find("." + className).addClass("active");
							}
						} else {
							if (el.css(cssProperty).toString().toLowerCase() === cssValue) {
								self.ui.toolbar.find("." + className).addClass("active");
							}
						}
					};

				if ("fullscreen" !== className) {
					self.ui.toolbar.find("." + className).removeClass("active");
				}

				if (control.tags || (control.options && control.options.tags)) {
					tags = control.tags || (control.options && control.options.tags);

					elm = element;
					while (elm) {
						if (elm.nodeType !== 1) {
							break;
						}

						if ($.inArray(elm.tagName.toLowerCase(), tags) !== -1) {
							self.ui.toolbar.find("." + className).addClass("active");
						}

						elm = elm.parentNode;
					}
				}

				if (control.css || (control.options && control.options.css)) {
					css = control.css || (control.options && control.options.css);
					el = $(element);

					while (el) {
						if (el[0].nodeType !== 1) {
							break;
						}
						$.each(css, checkActiveStatus);

						el = el.parent();
					}
				}
			});
		};

		this.ui.designMode = function () {
			var attempts = 3,
				self = this.self,
				runner = function (attempts) {
					if ("on" === self.editorDoc.designMode) {
						if (self.timers.designMode) {
							window.clearTimeout(self.timers.designMode);
						}

						// IE needs to reget the document element (this.editorDoc) after designMode was set
						if (self.innerDocument() !== self.editorDoc) {
							self.ui.initFrame();
						}

						return;
					}

					try {
						self.editorDoc.designMode = "on";
					} catch (e) {
					}

					attempts -= 1;
					if (attempts > 0) {
						self.timers.designMode = window.setTimeout(function () { runner(attempts); }, 100);
					}
				};

			runner(attempts);
		};

		this.destroy = function () {
			this.isDestroyed = true;

			var i, $form = this.element.closest("form");

			for (i = 0; i < this.timers.length; i += 1) {
				window.clearTimeout(this.timers[i]);
			}

			// Remove bindings
			$form.unbind(".wysiwyg");
			this.element.remove();
			$.removeData(this.original, "wysiwyg");
			$(this.original).show();
			return this;
		};

		this.getRangeText = function () {
			var r = this.getInternalRange();

			if (r.toString) {
				r = r.toString();
			} else if (r.text) {	// IE
				r = r.text;
			}

			return r;
		};
		//not used?
		this.execute = function (command, arg) {
			if (typeof (arg) === "undefined") {
				arg = null;
			}
			this.editorDoc.execCommand(command, false, arg);
		};

		this.extendOptions = function (options) {
			var controls = {};

			/**
			 * If the user set custom controls, we catch it, and merge with the
			 * defaults controls later.
			 */
			if ("object" === typeof options.controls) {
				controls = options.controls;
				delete options.controls;
			}

			options = $.extend(true, {}, this.defaults, options);
			options.controls = $.extend(true, {}, controls, this.controls, controls);

			if (options.rmUnusedControls) {
				$.each(options.controls, function (controlName) {
					if (!controls[controlName]) {
						delete options.controls[controlName];
					}
				});
			}

			return options;
		};

		this.ui.focus = function () {
			var self = this.self;

			self.editor.get(0).contentWindow.focus();
			return self;
		};

		this.ui.returnRange = function () {
			var self = this.self, sel;

			if (self.savedRange !== null) {
				if (window.getSelection) { //non IE and there is already a selection
					sel = window.getSelection();
					if (sel.rangeCount > 0) {
						sel.removeAllRanges();
					}
					try {
						sel.addRange(self.savedRange);
					} catch (e) {
						console.error(e);
					}
				} else if (window.document.createRange) { // non IE and no selection
					window.getSelection().addRange(self.savedRange);
				} else if (window.document.selection) { //IE
					self.savedRange.select();
				}

				self.savedRange = null;
			}
		};

		this.increaseFontSize = function () {
			if ($.browser.mozilla || $.browser.opera) {
				this.editorDoc.execCommand('increaseFontSize', false, null);
			} else if ($.browser.safari) {
				var newNode = this.editorDoc.createElement('big');
				this.getInternalRange().surroundContents(newNode);
			} else {
				console.error("Internet Explorer?");
			}
		};

		this.decreaseFontSize = function () {
			if ($.browser.mozilla || $.browser.opera) {
				this.editorDoc.execCommand('decreaseFontSize', false, null);
			} else if ($.browser.safari) {
				var newNode = this.editorDoc.createElement('small');
				this.getInternalRange().surroundContents(newNode);
			} else {
				console.error("Internet Explorer?");
			}
		};

		this.getContent = function () {
			return this.events.filter('getContent', this.editorDoc.body.innerHTML);
		};
		
		/**
		 * A jWysiwyg specific event system.
		 *
		 * Example:
		 * 
		 * $("#editor").getWysiwyg().events.bind("getContent", function (orig) {
		 *     return "<div id='content'>"+orgi+"</div>";
		 * });
		 * 
		 * This makes it so that when ever getContent is called, it is wrapped in a div#content.
		 */
		this.events = {
			_events : {},
			
			/**
			 * Similar to jQuery's bind, but for jWysiwyg only.
			 */
			bind : function (eventName, callback) {
				if(typeof(this._events.eventName) != "object") {
					this._events[eventName] = [];
				}
				this._events[eventName].push(callback);
			},
			
			/**
			 * Similar to jQuery's trigger, but for jWysiwyg only.
			 */
			trigger : function(eventName, args) {
				if(typeof(this._events.eventName) == "object") {
					var editor = this.editor;
					$.each(this._events, function (k,v) {
						if(typeof(v) == "function") {
							v.apply(editor, args);
						}
					});
				}
			},
			
			/**
			 * This "filters" `originalText` by passing it as the first argument to every callback
			 * with the name `eventName` and taking the return value and passing it to the next function.
			 *
			 * This function returns the result after all the callbacks have been applied to `originalText`.
			 */
			filter : function (eventName, originalText) {
				if(typeof(this._events.eventName) == "object") {
					var editor = this.editor;
					var args = Array.prototype.slice.call(arguments, 1);
					$.each(this._events, function (k,v) {
						if(typeof(v) == "function") {
							originalText = v.apply(editor, args);
						}
					});
				}
				return originalText;
			}
		};

		this.getElementByAttributeValue = function (tagName, attributeName, attributeValue) {
			var i, value, elements = this.editorDoc.getElementsByTagName(tagName);

			for (i = 0; i < elements.length; i += 1) {
				value = elements[i].getAttribute(attributeName);

				if ($.browser.msie) {
					/** IE add full path, so I check by the last chars. */
					value = value.substr(value.length - attributeValue.length);
				}

				if (value === attributeValue) {
					return elements[i];
				}
			}

			return false;
		};

		this.getInternalRange = function () {
			var selection = this.getInternalSelection();

			if (!selection) {
				return null;
			}

			if (selection.rangeCount && selection.rangeCount > 0) { // w3c
				return selection.getRangeAt(0);
			} else if (selection.createRange) { // ie
				return selection.createRange();
			}

			return null;
		};

		this.getInternalSelection = function () {
			// firefox: document.getSelection is deprecated
			if (this.editor.get(0).contentWindow) {
				if (this.editor.get(0).contentWindow.getSelection) {
					return this.editor.get(0).contentWindow.getSelection();
				}
				if (this.editor.get(0).contentWindow.selection) {
					return this.editor.get(0).contentWindow.selection;
				}
			}
			if (this.editorDoc.getSelection) {
				return this.editorDoc.getSelection();
			}
			if (this.editorDoc.selection) {
				return this.editorDoc.selection;
			}

			return null;
		};

		this.getRange = function () {
			var selection = this.getSelection();

			if (!selection) {
				return null;
			}

			if (selection.rangeCount && selection.rangeCount > 0) { // w3c
				selection.getRangeAt(0);
			} else if (selection.createRange) { // ie
				return selection.createRange();
			}

			return null;
		};

		this.getSelection = function () {
			return (window.getSelection) ? window.getSelection() : window.document.selection;
		};

		// :TODO: you can type long string and letters will be hidden because of overflow
		this.ui.grow = function () {
			var self = this.self,
				innerBody = $(self.editorDoc.body),
				innerHeight = $.browser.msie ? innerBody[0].scrollHeight : innerBody.height() + 2 + 20, // 2 - borders, 20 - to prevent content jumping on grow
				minHeight = self.ui.initialHeight,
				height = Math.max(innerHeight, minHeight);

			height = Math.min(height, self.options.maxHeight);

			self.editor.attr("scrolling", height < self.options.maxHeight ? "no" : "auto"); // hide scrollbar firefox
			innerBody.css("overflow", height < self.options.maxHeight ? "hidden" : ""); // hide scrollbar chrome

			self.editor.get(0).height = height;

			return self;
		};

		this.init = function (element, options) {
			var self = this,
				$form = $(element).closest("form"),
				newX = element.width || element.clientWidth || 0,
				newY = element.height || element.clientHeight || 0,
				i;

			this.options	= this.extendOptions(options);
			this.original	= element;
			this.ui.toolbar	= $(this.options.toolbarHtml);

			if ($.browser.msie && parseInt($.browser.version, 10) < 8) {
				this.options.autoGrow = false;
			}

			if (newX === 0 && element.cols) {
				newX = (element.cols * 8) + 21;
			}
			if (newY === 0 && element.rows) {
				newY = (element.rows * 16) + 16;
			}

			this.editor = $(window.location.protocol === "https:" ? '<iframe src="javascript:false;"></iframe>' : "<iframe></iframe>").attr("frameborder", "0");

			if (this.options.iFrameClass) {
				this.editor.addClass(this.options.iFrameClass);
			} else {
				this.editor.css({
					minHeight: (newY - 6).toString() + "px",
					// fix for issue 12 ( http://github.com/akzhan/jwysiwyg/issues/issue/12 )
					width: (newX > 50) ? (newX - 8).toString() + "px" : ""
				});
				if ($.browser.msie && parseInt($.browser.version, 10) < 7) {
					this.editor.css("height", newY.toString() + "px");
				}
			}
			/**
			 * http://code.google.com/p/jwysiwyg/issues/detail?id=96
			 */
			this.editor.attr("tabindex", $(element).attr("tabindex"));

			this.element = $("<div/>").addClass("wysiwyg");

			if (!this.options.iFrameClass) {
				this.element.css({
					width: (newX > 0) ? newX.toString() + "px" : "100%"
				});
			}

			$(element).hide().before(this.element);

			this.viewHTML = false;

			/**
			 * @link http://code.google.com/p/jwysiwyg/issues/detail?id=52
			 */
			this.initialContent = $(element).val();
			this.ui.initFrame();

			if (this.options.resizeOptions && $.fn.resizable) {
				this.element.resizable($.extend(true, {
					alsoResize: this.editor
				}, this.options.resizeOptions));
			}

			if (this.options.autoSave) {
				$form.bind("submit.wysiwyg", function () { self.autoSaveFunction(); });
			}

			$form.bind("reset.wysiwyg", function () { self.resetFunction(); });
		};

		this.ui.initFrame = function () {
			var self = this.self,
				stylesheet,
				growHandler,
				saveHandler;

			self.ui.appendControls();
			self.element.append(self.ui.toolbar)
				.append($("<div><!-- --></div>")
					.css({
						clear: "both"
					}))
				.append(self.editor);

			self.editorDoc = self.innerDocument();

			if (self.isDestroyed) {
				return null;
			}

			self.ui.designMode();
			self.editorDoc.open();
			self.editorDoc.write(
				self.options.html
					/**
					 * @link http://code.google.com/p/jwysiwyg/issues/detail?id=144
					 */
					.replace(/INITIAL_CONTENT/, function () { return self.wrapInitialContent(); })
			);
			self.editorDoc.close();

			$.wysiwyg.plugin.bind(self);

			$(self.editorDoc).trigger("initFrame.wysiwyg");

			$(self.editorDoc).bind("click.wysiwyg", function (event) {
				self.ui.checkTargets(event.target ? event.target : event.srcElement);
			});

			/**
			 * @link http://code.google.com/p/jwysiwyg/issues/detail?id=20
			 */
			$(self.original).focus(function () {
				if ($(this).filter(":visible")) {
					return;
				}
				self.ui.focus();
			});

			$(self.editorDoc).keydown(function (event) {
				var emptyContentRegex;
				if (event.keyCode === 8) { // backspace
					emptyContentRegex = /^<([\w]+)[^>]*>(<br\/?>)?<\/\1>$/;
					if (emptyContentRegex.test(self.getContent())) { // if content is empty
						event.stopPropagation(); // prevent remove single empty tag
						return false;
					}
				}
				return true;
			});

			if (!$.browser.msie) {
				$(self.editorDoc).keydown(function (event) {
					var controlName;

					/* Meta for Macs. tom@punkave.com */
					if (event.ctrlKey || event.metaKey) {
						for (controlName in self.controls) {
							if (self.controls[controlName].hotkey && self.controls[controlName].hotkey.ctrl) {
								if (event.keyCode === self.controls[controlName].hotkey.key) {
									self.triggerControl.apply(self, [controlName, self.controls[controlName]]);

									return false;
								}
							}
						}
					}

					return true;
				});
			} else if (self.options.brIE) {
				$(self.editorDoc).keydown(function (event) {
					if (event.keyCode === 13) {
						var rng = self.getRange();
						rng.pasteHTML("<br/>");
						rng.collapse(false);
						rng.select();

						return false;
					}

					return true;
				});
			}

			if (self.options.plugins.rmFormat.rmMsWordMarkup) {
				$(self.editorDoc).bind("keyup.wysiwyg", function (event) {
					if (event.ctrlKey || event.metaKey) {
						// CTRL + V (paste)
						if (86 === event.keyCode) {
							if ($.wysiwyg.rmFormat) {
								if ("object" === typeof (self.options.plugins.rmFormat.rmMsWordMarkup)) {
									$.wysiwyg.rmFormat.run(self, {rules: { msWordMarkup: self.options.plugins.rmFormat.rmMsWordMarkup }});
								} else {
									$.wysiwyg.rmFormat.run(self, {rules: { msWordMarkup: { enabled: true }}});
								}
							}
						}
					}
				});
			}

			if (self.options.autoSave) {
				$(self.editorDoc).keydown(function () { self.autoSaveFunction(); })
					.keyup(function () { self.autoSaveFunction(); })
					.mousedown(function () { self.autoSaveFunction(); })
					.bind($.support.noCloneEvent ? "input.wysiwyg" : "paste.wysiwyg", function () { self.autoSaveFunction(); });
			}

			if (self.options.autoGrow) {
				if (self.options.initialMinHeight !== null) {
					self.ui.initialHeight = self.options.initialMinHeight;
				} else {
					self.ui.initialHeight = $(self.editorDoc).height();
				}
				$(self.editorDoc.body).css("border", "1px solid white"); // cancel margin collapsing

				growHandler = function () {
					self.ui.grow();
				};

				$(self.editorDoc).keyup(growHandler);
				$(self.editorDoc).bind("editorRefresh.wysiwyg", growHandler);

				// fix when content height > textarea height
				self.ui.grow();
			}

			if (self.options.css) {
				if (String === self.options.css.constructor) {
					if ($.browser.msie) {
						stylesheet = self.editorDoc.createStyleSheet(self.options.css);
						$(stylesheet).attr({
							"media":	"all"
						});
					} else {
						stylesheet = $("<link/>").attr({
							"href":		self.options.css,
							"media":	"all",
							"rel":		"stylesheet",
							"type":		"text/css"
						});

						$(self.editorDoc).find("head").append(stylesheet);
					}
				} else {
					self.timers.initFrame_Css = window.setTimeout(function () {
						$(self.editorDoc.body).css(self.options.css);
					}, 0);
				}
			}

			if (self.initialContent.length === 0) {
				if ("function" === typeof (self.options.initialContent)) {
					self.setContent(self.options.initialContent());
				} else {
					self.setContent(self.options.initialContent);
				}
			}

			if (self.options.maxLength > 0) {
				$(self.editorDoc).keydown(function (event) {
					if ($(self.editorDoc).text().length >= self.options.maxLength && $.inArray(event.which, self.validKeyCodes) == -1) {
						event.preventDefault();
					}
				});
			}
			
			// Support event callbacks
			$.each(self.options.events, function (key, handler) {
				$(self.editorDoc).bind(key + ".wysiwyg", function (event) {
					// Trigger event handler, providing the event and api to 
					// support additional functionality.
					handler.apply(self.editorDoc, [event, self]);
				});
			});

			// restores selection properly on focus
			if ($.browser.msie) {
				// Event chain: beforedeactivate => focusout => blur.
				// Focusout & blur fired too late to handle internalRange() in dialogs.
				// When clicked on input boxes both got range = null
				$(self.editorDoc).bind("beforedeactivate.wysiwyg", function () {
					self.savedRange = self.getInternalRange();
				});
			} else {
				$(self.editorDoc).bind("blur.wysiwyg", function () {
					self.savedRange = self.getInternalRange();
				});
			}

			$(self.editorDoc.body).addClass("wysiwyg");
			if (self.options.events && self.options.events.save) {
				saveHandler = self.options.events.save;

				$(self.editorDoc).bind("keyup.wysiwyg", saveHandler);
				$(self.editorDoc).bind("change.wysiwyg", saveHandler);

				if ($.support.noCloneEvent) {
					$(self.editorDoc).bind("input.wysiwyg", saveHandler);
				} else {
					$(self.editorDoc).bind("paste.wysiwyg", saveHandler);
					$(self.editorDoc).bind("cut.wysiwyg", saveHandler);
				}
			}
			
			/**
			 * XHTML5 {@link https://github.com/akzhan/jwysiwyg/issues/152}
			 */
			if(self.options.xhtml5) {
				var replacements = {nbsp:"#00A0",iexcl:"#00A1",cent:"#00A2",pound:"#00A3",curren:"#00A4",yen:"#00A5",brvbar:"#00A6",sect:"#00A7",uml:"#00A8",copy:"#00A9",ordf:"#00AA",laquo:"#00AB",not:"#00AC",shy:"#00AD",reg:"#00AE",macr:"#00AF",deg:"#00B0",plusmn:"#00B1",sup2:"#00B2",sup3:"#00B3",acute:"#00B4",micro:"#00B5",para:"#00B6",middot:"#00B7",cedil:"#00B8",sup1:"#00B9",ordm:"#00BA",raquo:"#00BB",frac14:"#00BC",frac12:"#00BD",frac34:"#00BE",iquest:"#00BF",Agrave:"#00C0",Aacute:"#00C1",Acirc:"#00C2",Atilde:"#00C3",Auml:"#00C4",Aring:"#00C5",AElig:"#00C6",Ccedil:"#00C7",Egrave:"#00C8",Eacute:"#00C9",Ecirc:"#00CA",Euml:"#00CB",Igrave:"#00CC",Iacute:"#00CD",Icirc:"#00CE",Iuml:"#00CF",ETH:"#00D0",Ntilde:"#00D1",Ograve:"#00D2",Oacute:"#00D3",Ocirc:"#00D4",Otilde:"#00D5",Ouml:"#00D6",times:"#00D7",Oslash:"#00D8",Ugrave:"#00D9",Uacute:"#00DA",Ucirc:"#00DB",Uuml:"#00DC",Yacute:"#00DD",THORN:"#00DE",szlig:"#00DF",agrave:"#00E0",aacute:"#00E1",acirc:"#00E2",atilde:"#00E3",auml:"#00E4",aring:"#00E5",aelig:"#00E6",ccedil:"#00E7",egrave:"#00E8",eacute:"#00E9",ecirc:"#00EA",euml:"#00EB",igrave:"#00EC",iacute:"#00ED",icirc:"#00EE",iuml:"#00EF",eth:"#00F0",ntilde:"#00F1",ograve:"#00F2",oacute:"#00F3",ocirc:"#00F4",otilde:"#00F5",ouml:"#00F6",divide:"#00F7",oslash:"#00F8",ugrave:"#00F9",uacute:"#00FA",ucirc:"#00FB",uuml:"#00FC",yacute:"#00FD",thorn:"#00FE",yuml:"#00FF",OElig:"#0152",oelig:"#0153",Scaron:"#0160",scaron:"#0161",Yuml:"#0178",fnof:"#0192",circ:"#02C6",tilde:"#02DC",Alpha:"#0391",Beta:"#0392",Gamma:"#0393",Delta:"#0394",Epsilon:"#0395",Zeta:"#0396",Eta:"#0397",Theta:"#0398",Iota:"#0399",Kappa:"#039A",Lambda:"#039B",Mu:"#039C",Nu:"#039D",Xi:"#039E",Omicron:"#039F",Pi:"#03A0",Rho:"#03A1",Sigma:"#03A3",Tau:"#03A4",Upsilon:"#03A5",Phi:"#03A6",Chi:"#03A7",Psi:"#03A8",Omega:"#03A9",alpha:"#03B1",beta:"#03B2",gamma:"#03B3",delta:"#03B4",epsilon:"#03B5",zeta:"#03B6",eta:"#03B7",theta:"#03B8",iota:"#03B9",kappa:"#03BA",lambda:"#03BB",mu:"#03BC",nu:"#03BD",xi:"#03BE",omicron:"#03BF",pi:"#03C0",rho:"#03C1",sigmaf:"#03C2",sigma:"#03C3",tau:"#03C4",upsilon:"#03C5",phi:"#03C6",chi:"#03C7",psi:"#03C8",omega:"#03C9",thetasym:"#03D1",upsih:"#03D2",piv:"#03D6",ensp:"#2002",emsp:"#2003",thinsp:"#2009",zwnj:"#200C",zwj:"#200D",lrm:"#200E",rlm:"#200F",ndash:"#2013",mdash:"#2014",lsquo:"#2018",rsquo:"#2019",sbquo:"#201A",ldquo:"#201C",rdquo:"#201D",bdquo:"#201E",dagger:"#2020",Dagger:"#2021",bull:"#2022",hellip:"#2026",permil:"#2030",prime:"#2032",Prime:"#2033",lsaquo:"#2039",rsaquo:"#203A",oline:"#203E",frasl:"#2044",euro:"#20AC",image:"#2111",weierp:"#2118",real:"#211C",trade:"#2122",alefsym:"#2135",larr:"#2190",uarr:"#2191",rarr:"#2192",darr:"#2193",harr:"#2194",crarr:"#21B5",lArr:"#21D0",uArr:"#21D1",rArr:"#21D2",dArr:"#21D3",hArr:"#21D4",forall:"#2200",part:"#2202",exist:"#2203",empty:"#2205",nabla:"#2207",isin:"#2208",notin:"#2209",ni:"#220B",prod:"#220F",sum:"#2211",minus:"#2212",lowast:"#2217",radic:"#221A",prop:"#221D",infin:"#221E",ang:"#2220",and:"#2227",or:"#2228",cap:"#2229",cup:"#222A","int":"#222B",there4:"#2234",sim:"#223C",cong:"#2245",asymp:"#2248",ne:"#2260",equiv:"#2261",le:"#2264",ge:"#2265",sub:"#2282",sup:"#2283",nsub:"#2284",sube:"#2286",supe:"#2287",oplus:"#2295",otimes:"#2297",perp:"#22A5",sdot:"#22C5",lceil:"#2308",rceil:"#2309",lfloor:"#230A",rfloor:"#230B",lang:"#27E8",rang:"#27E9",loz:"#25CA",spades:"#2660",clubs:"#2663",hearts:"#2665",diams:"#2666"};
				this.events.bind("getContent", function (text) {
					return text.replace(/&([a-zA-Z0-9]+);/g, function (str, p1) {
						if(!replacements[p1]) {
							p1 = p1.toLowerCase();
						}
						return replacements[p1] ? "&"+replacements[p1]+";" : "";
					});
				});
			}
		};

		this.innerDocument = function () {
			var element = this.editor.get(0);

			if (element.nodeName.toLowerCase() === "iframe") {
				if (element.contentDocument) {				// Gecko
					return element.contentDocument;
				} else if (element.contentWindow) {			// IE
					return element.contentWindow.document;
				}

				if (this.isDestroyed) {
					return null;
				}

				console.error("Unexpected error in innerDocument");

				/*
				 return ( $.browser.msie )
				 ? document.frames[element.id].document
				 : element.contentWindow.document // contentDocument;
				 */
			}

			return element;
		};

		this.insertHtml = function (szHTML) {
			var img, range;

			if (!szHTML || szHTML.length === 0) {
				return this;
			}

			if ($.browser.msie) {
				this.ui.focus();
				this.editorDoc.execCommand("insertImage", false, "#jwysiwyg#");
				img = this.getElementByAttributeValue("img", "src", "#jwysiwyg#");
				if (img) {
					$(img).replaceWith(szHTML);
				}
			} else {	
				if ($.browser.mozilla) {
					range = this.getInternalRange();

					range.deleteContents();
					range.insertNode($(szHTML).get(0));
				} else {
					if (!this.editorDoc.execCommand("insertHTML", false, szHTML)) {
						this.editor.focus();
						/* :TODO: place caret at the end
						if (window.getSelection) {
						} else {
						}
						this.editor.focus();
						*/
						this.editorDoc.execCommand("insertHTML", false, szHTML);
					}
				}
			}

			return this;
		};

		this.parseControls = function () {
			var self = this;

			$.each(this.options.controls, function (controlName, control) {
				$.each(control, function (propertyName) {
					if (-1 === $.inArray(propertyName, self.availableControlProperties)) {
						throw controlName + '["' + propertyName + '"]: property "' + propertyName + '" not exists in Wysiwyg.availableControlProperties';
					}
				});
			});

			if (this.options.parseControls) {
				return this.options.parseControls.call(this);
			}

			return this.options.controls;
		};

		this.removeFormat = function () {
			if ($.browser.msie) {
				this.ui.focus();
			}

			if (this.options.removeHeadings) {
				this.editorDoc.execCommand("formatBlock", false, "<p>"); // remove headings
			}

			this.editorDoc.execCommand("removeFormat", false, null);
			this.editorDoc.execCommand("unlink", false, null);

			if ($.wysiwyg.rmFormat && $.wysiwyg.rmFormat.enabled) {
				$.wysiwyg.rmFormat.run(this);
			}

			return this;
		};

		this.ui.removeHoverClass = function () {
			$(this).removeClass("wysiwyg-button-hover");
		};

		this.resetFunction = function () {
			this.setContent(this.initialContent);
			this.saveContent();
		};

		this.saveContent = function () {
			if (this.original) {
				var content, newContent;

				if (this.viewHTML) {
					this.setContent($(this.original).val());
				}

				content = this.getContent();

				if (this.options.rmUnwantedBr) {
					content = content.replace(/<br\/?>$/, "");
				}

				if (this.options.replaceDivWithP) {
					newContent = $("<div/>").addClass("temp").append(content);

					newContent.children("div").each(function () {
						var element = $(this), p = element.find("p"), i;

						if (0 === p.length) {
							p = $("<p></p>");

							if (this.attributes.length > 0) {
								for (i = 0; i < this.attributes.length; i += 1) {
									p.attr(this.attributes[i].name, element.attr(this.attributes[i].name));
								}
							}

							p.append(element.html());

							element.replaceWith(p);
						}
					});
					
					content = newContent.html();
				}

				$(this.original).val(content);

				if (this.options.events && this.options.events.save) {
					this.options.events.save.call(this);
				}
			}

			return this;
		};

		this.setContent = function (newContent) {
			this.editorDoc.body.innerHTML = newContent;
			return this;
		};

		this.triggerControl = function (name, control) {
			var cmd = control.command || name,
				args = control["arguments"] || [];

			if (control.exec) {
				control.exec.apply(this);
			} else {
				this.ui.focus();
				this.ui.withoutCss();
				// when click <Cut>, <Copy> or <Paste> got "Access to XPConnect service denied" code: "1011"
				// in Firefox untrusted JavaScript is not allowed to access the clipboard
				try {
					this.editorDoc.execCommand(cmd, false, args);
				} catch (e) {
					console.error(e);
				}
			}

			if (this.options.autoSave) {
				this.autoSaveFunction();
			}
		};

		this.triggerControlCallback = function (name) {
			$(window).trigger("trigger-" + name + ".wysiwyg", [this]);
		};

		this.ui.withoutCss = function () {
			var self = this.self;

			if ($.browser.mozilla) {
				try {
					self.editorDoc.execCommand("styleWithCSS", false, false);
				} catch (e) {
					try {
						self.editorDoc.execCommand("useCSS", false, true);
					} catch (e2) {
					}
				}
			}

			return self;
		};

		this.wrapInitialContent = function () {
			var content = this.initialContent,
				found = content.match(/<\/?p>/gi);

			if (!found) {
				return "<p>" + content + "</p>";
			} else {
				// :TODO: checking/replacing
			}

			return content;
		};
	}

	/*
	 * Wysiwyg namespace: public properties and methods
	 */
	$.wysiwyg = {
		messages: {
			noObject: "Something goes wrong, check object"
		},

		/**
		 * Custom control support by Alec Gorge ( http://github.com/alecgorge )
		 */
		addControl: function (object, name, settings) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg"),
					customControl = {},
					toolbar;

				if (!oWysiwyg) {
					return this;
				}

				customControl[name] = $.extend(true, {visible: true, custom: true}, settings);
				$.extend(true, oWysiwyg.options.controls, customControl);

				// render new toolbar
				toolbar = $(oWysiwyg.options.toolbarHtml);
				oWysiwyg.ui.toolbar.replaceWith(toolbar);
				oWysiwyg.ui.toolbar = toolbar;
				oWysiwyg.ui.appendControls();
			});
		},

		clear: function (object) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				oWysiwyg.setContent("");
				oWysiwyg.saveContent();
			});
		},

		console: console, // let our console be available for extensions

		destroy: function (object) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				oWysiwyg.destroy();
			});
		},

		"document": function (object) {
			// no chains because of return
			var oWysiwyg = object.data("wysiwyg");

			if (!oWysiwyg) {
				return undefined;
			}

			return $(oWysiwyg.editorDoc);
		},

		getContent: function (object) {
			// no chains because of return
			var oWysiwyg = object.data("wysiwyg");

			if (!oWysiwyg) {
				return undefined;
			}

			return oWysiwyg.getContent();
		},

		init: function (object, options) {
			return object.each(function () {
				var opts = $.extend(true, {}, options),
					obj;

				// :4fun:
				// remove this textarea validation and change line in this.saveContent function
				// $(this.original).val(content); to $(this.original).html(content);
				// now you can make WYSIWYG editor on h1, p, and many more tags
				if (("textarea" !== this.nodeName.toLowerCase()) || $(this).data("wysiwyg")) {
					return;
				}

				obj = new Wysiwyg();
				obj.init(this, opts);
				$.data(this, "wysiwyg", obj);

				$(obj.editorDoc).trigger("afterInit.wysiwyg");
			});
		},

		insertHtml: function (object, szHTML) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				oWysiwyg.insertHtml(szHTML);
			});
		},

		plugin: {
			listeners: {},

			bind: function (Wysiwyg) {
				var self = this;

				$.each(this.listeners, function (action, handlers) {
					var i, plugin;

					for (i = 0; i < handlers.length; i += 1) {
						plugin = self.parseName(handlers[i]);

						$(Wysiwyg.editorDoc).bind(action + ".wysiwyg", {plugin: plugin}, function (event) {
							$.wysiwyg[event.data.plugin.name][event.data.plugin.method].apply($.wysiwyg[event.data.plugin.name], [Wysiwyg]);
						});
					}
				});
			},

			exists: function (name) {
				var plugin;

				if ("string" !== typeof (name)) {
					return false;
				}

				plugin = this.parseName(name);

				if (!$.wysiwyg[plugin.name] || !$.wysiwyg[plugin.name][plugin.method]) {
					return false;
				}

				return true;
			},

			listen: function (action, handler) {
				var plugin;

				plugin = this.parseName(handler);

				if (!$.wysiwyg[plugin.name] || !$.wysiwyg[plugin.name][plugin.method]) {
					return false;
				}

				if (!this.listeners[action]) {
					this.listeners[action] = [];
				}

				this.listeners[action].push(handler);

				return true;
			},

			parseName: function (name) {
				var elements;

				if ("string" !== typeof (name)) {
					return false;
				}

				elements = name.split(".");

				if (2 > elements.length) {
					return false;
				}

				return {name: elements[0], method: elements[1]};
			},

			register: function (data) {
				if (!data.name) {
					console.error("Plugin name missing");
				}

				$.each($.wysiwyg, function (pluginName) {
					if (pluginName === data.name) {
						console.error("Plugin with name '" + data.name + "' was already registered");
					}
				});

				$.wysiwyg[data.name] = data;

				return true;
			}
		},

		removeFormat: function (object) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				oWysiwyg.removeFormat();
			});
		},

		save: function (object) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				oWysiwyg.saveContent();
			});
		},

		selectAll: function (object) {
			var oWysiwyg = object.data("wysiwyg"), oBody, oRange, selection;

			if (!oWysiwyg) {
				return this;
			}

			oBody = oWysiwyg.editorDoc.body;
			if (window.getSelection) {
				selection = oWysiwyg.getInternalSelection();
				selection.selectAllChildren(oBody);
			} else {
				oRange = oBody.createTextRange();
				oRange.moveToElementText(oBody);
				oRange.select();
			}
		},

		setContent: function (object, newContent) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				oWysiwyg.setContent(newContent);
				oWysiwyg.saveContent();
			});
		},

		triggerControl: function (object, controlName) {
			return object.each(function () {
				var oWysiwyg = $(this).data("wysiwyg");

				if (!oWysiwyg) {
					return this;
				}

				if (!oWysiwyg.controls[controlName]) {
					console.error("Control '" + controlName + "' not exists");
				}

				oWysiwyg.triggerControl.apply(oWysiwyg, [controlName, oWysiwyg.controls[controlName]]);
			});
		},

		utils: {
			extraSafeEntities: [["<", ">", "'", '"', " "], [32]],

			encodeEntities: function (str) {
				var self = this, aStr, aRet = [];

				if (this.extraSafeEntities[1].length === 0) {
					$.each(this.extraSafeEntities[0], function (i, ch) {
						self.extraSafeEntities[1].push(ch.charCodeAt());
					});
				}
				aStr = str.split("");
				$.each(aStr, function (i) {
					var iC = aStr[i].charCodeAt();
					if ($.inArray(iC, self.extraSafeEntities[1]) && (iC < 65 || iC > 127 || (iC > 90 && iC < 97))) {
						aRet.push('&#' + iC + ';');
					} else {
						aRet.push(aStr[i]);
					}
				});

				return aRet.join('');
			}
		}
	};

	$.fn.wysiwyg = function (method) {
		var args = arguments, plugin;

		if ("undefined" !== typeof $.wysiwyg[method]) {
			// set argument object to undefined
			args = Array.prototype.concat.call([args[0]], [this], Array.prototype.slice.call(args, 1));
			return $.wysiwyg[method].apply($.wysiwyg, Array.prototype.slice.call(args, 1));
		} else if ("object" === typeof method || !method) {
			Array.prototype.unshift.call(args, this);
			return $.wysiwyg.init.apply($.wysiwyg, args);
		} else if ($.wysiwyg.plugin.exists(method)) {
			plugin = $.wysiwyg.plugin.parseName(method);
			args = Array.prototype.concat.call([args[0]], [this], Array.prototype.slice.call(args, 1));
			return $.wysiwyg[plugin.name][plugin.method].apply($.wysiwyg[plugin.name], Array.prototype.slice.call(args, 1));
		} else {
			console.error("Method '" +  method + "' does not exist on jQuery.wysiwyg.\nTry to include some extra controls or plugins");
		}
	};
	
	$.fn.getWysiwyg = function () {
		return $.data(this, "wysiwyg");
	};
})(jQuery);

;
/**
 * Controls: Colorpicker plugin
 * 
 * Depends on jWYSIWYG, (farbtastic || other colorpicker plugins)
 */
(function ($) {
	if (undefined === $.wysiwyg) {
		throw "wysiwyg.colorpicker.js depends on $.wysiwyg";
	}

	if (!$.wysiwyg.controls) {
		$.wysiwyg.controls = {};
	}

	/*
	 * Wysiwyg namespace: public properties and methods
	 */
	$.wysiwyg.controls.colorpicker = {
		modalOpen: false,
		color: {
			back: {
				prev: "#ffffff",
				palette: []
			},
			fore: {
				prev: "#123456",
				palette: []
			}
		},

		addColorToPalette: function (type, color) {
			if (-1 === $.inArray(color, this.color[type].palette)) {
				this.color[type].palette.push(color);
			} else {
				this.color[type].palette.sort(function (a, b) {
					if (a === color) {
						return 1;
					}

					return 0;
				});
			}
		},

		init: function (Wysiwyg) {
			if ($.wysiwyg.controls.colorpicker.modalOpen === true) {
				return false;
			} else {
				$.wysiwyg.controls.colorpicker.modalOpen = true;
			}
			var self = this, elements, dialog, colorpickerHtml, dialogReplacements, key, translation;

			dialogReplacements = {
				legend: "Colorpicker",
				color: "Color",
				submit: "Apply",
				reset: "Cancel"
			};

			colorpickerHtml = '<form class="wysiwyg"><fieldset><legend>{legend}</legend>' +
				'<ul class="palette"></ul>' +
				'<label>{color}: <input type="text" name="color" value="#123456"/></label>' +
				'<div class="wheel"></div>' +
				'<input type="submit" class="button" value="{submit}"/> ' +
				'<input type="reset" value="{reset}"/></fieldset></form>';

			for (key in dialogReplacements) {
				if ($.wysiwyg.i18n) {
					translation = $.wysiwyg.i18n.t(dialogReplacements[key], "dialogs.colorpicker");

					if (translation === dialogReplacements[key]) { // if not translated search in dialogs 
						translation = $.wysiwyg.i18n.t(dialogReplacements[key], "dialogs");
					}

					dialogReplacements[key] = translation;
				}

				colorpickerHtml = colorpickerHtml.replace("{" + key + "}", dialogReplacements[key]);
			}

			if ($.modal) {
				elements = $(colorpickerHtml);

				if ($.farbtastic) {
					this.renderPalette(elements, "fore");
					elements.find(".wheel").farbtastic(elements.find("input:text"));
				}

				$.modal(elements.html(), {
					maxWidth: Wysiwyg.defaults.formWidth,
					maxHeight: Wysiwyg.defaults.formHeight,
					overlayClose: true,

					onShow: function (dialog) {
						$("input:submit", dialog.data).click(function (e) {
							var color = $('input[name="color"]', dialog.data).val();
							self.color.fore.prev = color;
							self.addColorToPalette("fore", color);

							if ($.browser.msie) {
								Wysiwyg.ui.returnRange();
							}

							Wysiwyg.editorDoc.execCommand('ForeColor', false, color);
							$.modal.close();
							return false;
						});
						$("input:reset", dialog.data).click(function (e) {
							if ($.browser.msie) {
								Wysiwyg.ui.returnRange();
							}

							$.modal.close();
							return false;
						});
						$("fieldset", dialog.data).click(function (e) {
							e.stopPropagation();
						});
					},

					onClose: function (dialog) {
						$.wysiwyg.controls.colorpicker.modalOpen = false;
						$.modal.close();
					}
				});
			} else if ($.fn.dialog) {
				elements = $(colorpickerHtml);

				if ($.farbtastic) {
					this.renderPalette(elements, "fore");
					elements.find(".wheel").farbtastic(elements.find("input:text"));
				}

				dialog = elements.appendTo("body");
				dialog.dialog({
					modal: true,

					open: function (event, ui) {
						$("input:submit", elements).click(function (e) {
							var color = $('input[name="color"]', dialog).val();
							self.color.fore.prev = color;
							self.addColorToPalette("fore", color);

							if ($.browser.msie) {
								Wysiwyg.ui.returnRange();
							}

							Wysiwyg.editorDoc.execCommand('ForeColor', false, color);
							$(dialog).dialog("close");
							return false;
						});
						$("input:reset", elements).click(function (e) {
							if ($.browser.msie) {
								Wysiwyg.ui.returnRange();
							}

							$(dialog).dialog("close");
							return false;
						});
						$('fieldset', elements).click(function (e) {
							e.stopPropagation();
						});
					},

					close: function (event, ui) {
						$.wysiwyg.controls.colorpicker.modalOpen = false;
						dialog.dialog("destroy");
						dialog.remove();
					}
				});
			} else {
				if ($.farbtastic) {
					elements = $("<div/>")
						.css({"position": "fixed",
							"z-index": 2000,
							"left": "50%", "top": "50%", "background": "rgb(0, 0, 0)",
							"margin-top": -1 * Math.round(Wysiwyg.defaults.formHeight / 2),
							"margin-left": -1 * Math.round(Wysiwyg.defaults.formWidth / 2)})
						.html(colorpickerHtml);
					this.renderPalette(elements, "fore");
					elements.find("input[name=color]").val(self.color.fore.prev);
					elements.find(".wheel").farbtastic(elements.find("input:text"));
					$("input:submit", elements).click(function (event) {
						var color = $('input[name="color"]', elements).val();
						self.color.fore.prev = color;
						self.addColorToPalette("fore", color);

						if ($.browser.msie) {
							Wysiwyg.ui.returnRange();
						}

						Wysiwyg.editorDoc.execCommand('ForeColor', false, color);

						$(elements).remove();
						$.wysiwyg.controls.colorpicker.modalOpen = false;
						return false;
					});
					$("input:reset", elements).click(function (event) {

						if ($.browser.msie) {
							Wysiwyg.ui.returnRange();
						}

						$(elements).remove();
						$.wysiwyg.controls.colorpicker.modalOpen = false;
						return false;
					});
					$("body").append(elements);
					elements.click(function(e) {
					  e.stopPropagation();
					});
				}
			}
		},

		renderPalette: function (jqObj, type) {
			var palette = jqObj.find(".palette"),
				bind = function () {
					var color = $(this).text();
					jqObj.find("input[name=color]").val(color);
					// farbtastic binds on keyup
					if ($.farbtastic) {
						jqObj.find("input[name=color]").trigger("keyup");
					}
				},
				colorExample,
				colorSelect,
				i;

			for (i = this.color[type].palette.length - 1; i > -1; i -= 1) {
				colorExample = $("<div/>").css({
					"float": "left",
					"width": "16px",
					"height": "16px",
					"margin": "0px 5px 0px 0px",
					"background-color": this.color[type].palette[i]
				});

				colorSelect = $("<li>" + this.color[type].palette[i] + "</li>")
					.css({"float": "left", "list-style": "none"})
					.append(colorExample)
					.bind("click.wysiwyg", bind);

				palette.append(colorSelect).css({"margin": "0px", "padding": "0px"});
			}
		}
	};
})(jQuery);
;
/**
 * Controls: Table plugin
 * 
 * Depends on jWYSIWYG
 */
(function ($) {
	if (undefined === $.wysiwyg) {
		throw "wysiwyg.table.js depends on $.wysiwyg";
	}

	if (!$.wysiwyg.controls) {
		$.wysiwyg.controls = {};
	}

	var insertTable = function (colCount, rowCount, filler) {
		if (isNaN(rowCount) || isNaN(colCount) || rowCount === null || colCount === null) {
			return;
		}

		var i, j, html = ['<table border="1" style="width: 100%;"><tbody>'];

		colCount = parseInt(colCount, 10);
		rowCount = parseInt(rowCount, 10);

		if (filler === null) {
			filler = "&nbsp;";
		}
		filler = "<td>" + filler + "</td>";

		for (i = rowCount; i > 0; i -= 1) {
			html.push("<tr>");
			for (j = colCount; j > 0; j -= 1) {
				html.push(filler);
			}
			html.push("</tr>");
		}
		html.push("</tbody></table>");

		return this.insertHtml(html.join(""));
	};

	/*
	 * Wysiwyg namespace: public properties and methods
	 */
	$.wysiwyg.controls.table = function (Wysiwyg) {
		var dialog, colCount, rowCount, formTableHtml,
			formTextLegend = "Insert table",
			formTextCols   = "Count of columns",
			formTextRows   = "Count of rows",
			formTextSubmit = "Insert table",
			formTextReset  = "Cancel";

		if ($.wysiwyg.i18n) {
			formTextLegend = $.wysiwyg.i18n.t(formTextLegend, "dialogs.table");
			formTextCols = $.wysiwyg.i18n.t(formTextCols, "dialogs.table");
			formTextRows = $.wysiwyg.i18n.t(formTextRows, "dialogs.table");
			formTextSubmit = $.wysiwyg.i18n.t(formTextSubmit, "dialogs.table");
			formTextReset = $.wysiwyg.i18n.t(formTextReset, "dialogs");
		}

		formTableHtml = '<form class="wysiwyg"><fieldset><legend>' + formTextLegend + '</legend>' +
			'<label>' + formTextCols + ': <input type="text" name="colCount" value="3" /></label>' +
			'<label>' + formTextRows + ': <input type="text" name="rowCount" value="3" /></label>' +
			'<input type="submit" class="button" value="' + formTextSubmit + '"/> ' +
			'<input type="reset" value="' + formTextReset + '"/></fieldset></form>';

		if (!Wysiwyg.insertTable) {
			Wysiwyg.insertTable = insertTable;
		}

		if ($.fn.modal) {
			$.modal(formTableHtml, {
				onShow: function (dialog) {
					$("input:submit", dialog.data).click(function (e) {
						e.preventDefault();
						rowCount = $('input[name="rowCount"]', dialog.data).val();
						colCount = $('input[name="colCount"]', dialog.data).val();

						Wysiwyg.insertTable(colCount, rowCount, Wysiwyg.defaults.tableFiller);
						$.modal.close();
					});
					$("input:reset", dialog.data).click(function (e) {
						e.preventDefault();
						$.modal.close();
					});
				},
				maxWidth: Wysiwyg.defaults.formWidth,
				maxHeight: Wysiwyg.defaults.formHeight,
				overlayClose: true
			});
		} else if ($.fn.dialog) {
			dialog = $(formTableHtml).appendTo("body");
			dialog.dialog({
				modal: true,
				open: function (event, ui) {
					$("input:submit", dialog).click(function (e) {
						e.preventDefault();
						rowCount = $('input[name="rowCount"]', dialog).val();
						colCount = $('input[name="colCount"]', dialog).val();

						Wysiwyg.insertTable(colCount, rowCount, Wysiwyg.defaults.tableFiller);
						$(dialog).dialog("close");
					});
					$("input:reset", dialog).click(function (e) {
						e.preventDefault();
						$(dialog).dialog("close");
					});
				},
				close: function (event, ui) {
					dialog.dialog("destroy");
				}
			});
		} else {
			colCount = prompt(formTextCols, "3");
			rowCount = prompt(formTextRows, "3");

			Wysiwyg.insertTable(colCount, rowCount, Wysiwyg.defaults.tableFiller);
		}

		$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");
	};

	$.wysiwyg.insertTable = function (object, colCount, rowCount, filler) {
		return object.each(function () {
			var Wysiwyg = $(this).data("wysiwyg");

			if (!Wysiwyg.insertTable) {
				Wysiwyg.insertTable = insertTable;
			}

			if (!Wysiwyg) {
				return this;
			}

			Wysiwyg.insertTable(colCount, rowCount, filler);
			$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");

			return this;
		});
	};
})(jQuery);
;
/**
 * Controls: Image plugin
 *
 * Depends on jWYSIWYG
 */
(function ($) {
	if (undefined === $.wysiwyg) {
		throw "wysiwyg.image.js depends on $.wysiwyg";
	}

	if (!$.wysiwyg.controls) {
		$.wysiwyg.controls = {};
	}

	/*
	 * Wysiwyg namespace: public properties and methods
	 */
	$.wysiwyg.controls.image = {
		init: function (Wysiwyg) {
			var self = this, elements, dialog, formImageHtml, dialogReplacements, key, translation,
				img = {
					alt: "",
					self: Wysiwyg.dom.getElement("img"), // link to element node
					src: "http://",
					title: ""
				};

			dialogReplacements = {
				legend	: "Insert Image",
				preview : "Preview",
				url     : "URL",
				title   : "Title",
				description : "Description",
				width   : "Width",
				height  : "Height",
				original : "Original W x H",
				float	: "Float",
				floatNone : "None",
				floatLeft : "Left",
				floatRight : "Right",
				submit  : "Insert Image",
				reset   : "Cancel"
			};

			formImageHtml = '<form class="wysiwyg"><fieldset><legend>{legend}</legend>' +
				'<label>{preview}: <img src="" alt="{preview}" style="float: left; margin: 5px; width: 80px; height: 60px; border: 1px solid rgb(192, 192, 192);"/></label>' +
				'<label>{url}: <input type="text" name="src" value=""/></label>' +
				'<label>{title}: <input type="text" name="imgtitle" value=""/></label>' +
				'<label>{description}: <input type="text" name="description" value=""/></label>' +
				'<label>{width} x {height}: <input type="text" name="width" value="" class="width"/> x <input type="text" name="height" value="" class="height"/></label>' +
				'<label>{original}: <input type="text" name="naturalWidth" value="" class="width" disabled="disabled"/> x ' +
				'<input type="text" name="naturalHeight" value="" class="height" disabled="disabled"/></label>' +
				'<label>{float}: <select name="float">' + 
				'<option value="">{floatNone}</option>' +
				'<option value="left">{floatLeft}</option>' +
				'<option value="right">{floatRight}</option></select></label>' +
				'<input type="submit" class="button" value="{submit}"/> ' +
				'<input type="reset" value="{reset}"/></fieldset></form>';

			for (key in dialogReplacements) {
				if ($.wysiwyg.i18n) {
					translation = $.wysiwyg.i18n.t(dialogReplacements[key], "dialogs.image");

					if (translation === dialogReplacements[key]) { // if not translated search in dialogs 
						translation = $.wysiwyg.i18n.t(dialogReplacements[key], "dialogs");
					}

					dialogReplacements[key] = translation;
				}

				formImageHtml = formImageHtml.replace("{" + key + "}", dialogReplacements[key]);
			}

			if (img.self) {
				img.src = img.self.src ? img.self.src : "";
				img.alt = img.self.alt ? img.self.alt : "";
				img.title = img.self.title ? img.self.title : "";
				img.width = img.self.width ? img.self.width : "";
				img.height = img.self.height ? img.self.height : "";
			}

			if (true /*mshipko: replaced default JWysiwyg dialog with standard browser prompt*/) {
                var defaultValue = "http://";
                var imageUrl = prompt("Insert image", defaultValue);
                if (imageUrl && imageUrl !== "" && imageUrl !== defaultValue) {
                    Wysiwyg.insertHtml('<img src=\"' + imageUrl + '\">');
                }
            } else if ($.modal) {
				elements = $(formImageHtml);
				elements = self.makeForm(elements, img);

				$.modal(elements, {
					onShow: function (dialog) {
						$("input:submit", dialog.data).click(function (e) {
							self.processInsert(dialog.container, Wysiwyg, img);

							$.modal.close();
							return false;
						});
						$("input:reset", dialog.data).click(function (e) {
							$.modal.close();
							return false;
						});
						$("fieldset", dialog.data).click(function (e) {
							e.stopPropagation();
						});
					},
					maxWidth: Wysiwyg.defaults.formWidth,
					maxHeight: Wysiwyg.defaults.formHeight,
					overlayClose: true
				});
			} else if ($.fn.dialog) {
				elements = $(formImageHtml);
				elements = self.makeForm(elements, img);

				dialog = elements.appendTo("body");
				dialog.dialog({
					modal: true,
					open: function (ev, ui) {
						$("input:submit", dialog).click(function (e) {
							self.processInsert(dialog.container, Wysiwyg, img);

							$(dialog).dialog("close");
							return false;
						});
						$("input:reset", dialog).click(function (e) {
							$(dialog).dialog("close");
							return false;
						});
						$('fieldset', dialog).click(function (e) {
							e.stopPropagation();
						});
					},
					close: function (ev, ui) {
						dialog.dialog("destroy");
					}
				});
			} else {
				if ($.browser.msie) {
					Wysiwyg.ui.focus();
					Wysiwyg.editorDoc.execCommand("insertImage", true, null);
				} else {
					elements = $("<div/>")
						.css({"position": "fixed",
							"z-index": 2000,
							"left": "50%", "top": "50%", "background": "rgb(0, 0, 0)",
							"margin-top": -1 * Math.round(Wysiwyg.defaults.formHeight / 2),
							"margin-left": -1 * Math.round(Wysiwyg.defaults.formWidth / 2)})
						.html(formImageHtml);
					elements = self.makeForm(elements, img);

					$("input:submit", elements).click(function (event) {
						self.processInsert(elements, Wysiwyg, img);

						$(elements).remove();
						return false;
					});
					$("input:reset", elements).click(function (event) {
						if ($.browser.msie) {
							Wysiwyg.ui.returnRange();
						}

						$(elements).remove();
						return false;
					});

					$("body").append(elements);
					elements.click(function(e) {
						e.stopPropagation();
					});
				}
			}

			$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");
		},

		processInsert: function (context, Wysiwyg, img) {
			var image,
				url = $('input[name="src"]', context).val(),
				title = $('input[name="imgtitle"]', context).val(),
				description = $('input[name="description"]', context).val(),
				width = $('input[name="width"]', context).val(),
				height = $('input[name="height"]', context).val(),
				styleFloat = $('select[name="float"]', context).val(),
				style = [],
				found,
				baseUrl;

			if (Wysiwyg.options.controlImage.forceRelativeUrls) {
				baseUrl = window.location.protocol + "//" + window.location.hostname;
				if (0 === url.indexOf(baseUrl)) {
					url = url.substr(baseUrl.length);
				}
			}

			if (img.self) {
				// to preserve all img attributes
				$(img.self).attr("src", url)
					.attr("title", title)
					.attr("alt", description)
					.css("float", styleFloat);

				if (width.toString().match(/^[0-9]+(px|%)?$/)) {
					$(img.self).css("width", width);
				} else {
					$(img.self).css("width", "");
				}

				if (height.toString().match(/^[0-9]+(px|%)?$/)) {
					$(img.self).css("height", height);
				} else {
					$(img.self).css("height", "");
				}
			} else {
				found = width.toString().match(/^[0-9]+(px|%)?$/);
				if (found) {
					if (found[1]) {
						style.push("width: " + width + ";");
					} else {
						style.push("width: " + width + "px;");
					}
				}

				found = height.toString().match(/^[0-9]+(px|%)?$/);
				if (found) {
					if (found[1]) {
						style.push("height: " + height + ";");
					} else {
						style.push("height: " + height + "px;");
					}
				}

				if (styleFloat.length > 0) {
					style.push("float: " + styleFloat + ";");
				}

				if (style.length > 0) {
					style = ' style="' + style.join(" ") + '"';
				}

				image = "<img src='" + url + "' title='" + title + "' alt='" + description + "'" + style + "/>";
				Wysiwyg.insertHtml(image);
			}
		},

		makeForm: function (form, img) {
			form.find("input[name=src]").val(img.src);
			form.find("input[name=imgtitle]").val(img.title);
			form.find("input[name=description]").val(img.alt);
			form.find('input[name="width"]').val(img.width);
			form.find('input[name="height"]').val(img.height);
			form.find('img').attr("src", img.src);

			form.find('img').bind("load", function () {
				if (form.find('img').attr("naturalWidth")) {
					form.find('input[name="naturalWidth"]').val(form.find('img').attr("naturalWidth"));
					form.find('input[name="naturalHeight"]').val(form.find('img').attr("naturalHeight"));
				}
			});

			form.find("input[name=src]").bind("change", function () {
				form.find('img').attr("src", this.value);
			});

			return form;
		}
	};

	$.wysiwyg.insertImage = function (object, url, attributes) {
		return object.each(function () {
			var self = $(this).data("wysiwyg"),
				image,
				attribute;

			if (!self) {
				return this;
			}

			if (!url || url.length === 0) {
				return this;
			}

			if ($.browser.msie) {
				self.ui.focus();
			}

			if (attributes) {
				self.editorDoc.execCommand("insertImage", false, "#jwysiwyg#");
				image = self.getElementByAttributeValue("img", "src", "#jwysiwyg#");

				if (image) {
					image.src = url;

					for (attribute in attributes) {
						if (attributes.hasOwnProperty(attribute)) {
							image.setAttribute(attribute, attributes[attribute]);
						}
					}
				}
			} else {
				self.editorDoc.execCommand("insertImage", false, url);
			}

			$(self.editorDoc).trigger("editorRefresh.wysiwyg");

			return this;
		});
	};
})(jQuery);

;
/**
 * Controls: Link plugin
 *
 * Depends on jWYSIWYG
 *
 * By: Esteban Beltran (academo) <sergies@gmail.com>
 */
(function ($) {
	if (undefined === $.wysiwyg) {
		throw "wysiwyg.image.js depends on $.wysiwyg";
	}

	if (!$.wysiwyg.controls) {
		$.wysiwyg.controls = {};
	}

	/*
	* Wysiwyg namespace: public properties and methods
	*/
	$.wysiwyg.controls.link = {
		init: function (Wysiwyg) {
			var self = this, elements, dialog, url, a, selection,
				formLinkHtml, formTextLegend, formTextUrl, formTextTitle, formTextTarget,
				formTextSubmit, formTextReset,
				baseUrl;

			formTextLegend  = "Insert Link";
			formTextUrl     = "Link URL";
			formTextTitle   = "Link Title";
			formTextTarget  = "Link Target";
			formTextSubmit  = "Insert Link";
			formTextReset   = "Cancel";

			if ($.wysiwyg.i18n) {
				formTextLegend = $.wysiwyg.i18n.t(formTextLegend, "dialogs.link");
				formTextUrl    = $.wysiwyg.i18n.t(formTextUrl, "dialogs.link");
				formTextTitle  = $.wysiwyg.i18n.t(formTextTitle, "dialogs.link");
				formTextTarget = $.wysiwyg.i18n.t(formTextTarget, "dialogs.link");
				formTextSubmit = $.wysiwyg.i18n.t(formTextSubmit, "dialogs.link");
				formTextReset  = $.wysiwyg.i18n.t(formTextReset, "dialogs");
			}

			formLinkHtml = '<form class="wysiwyg"><fieldset><legend>' + formTextLegend + '</legend>' +
				'<label>' + formTextUrl + ': <input type="text" name="linkhref" value=""/></label>' +
				'<label>' + formTextTitle + ': <input type="text" name="linktitle" value=""/></label>' +
				'<label>' + formTextTarget + ': <input type="text" name="linktarget" value=""/></label>' +
				'<input type="submit" class="button" value="' + formTextSubmit + '"/> ' +
				'<input type="reset" value="' + formTextReset + '"/></fieldset></form>';

			a = {
				self: Wysiwyg.dom.getElement("a"), // link to element node
				href: "http://",
				title: "",
				target: ""
			};

			if (a.self) {
				a.href = a.self.href ? a.self.href : a.href;
				a.title = a.self.title ? a.self.title : "";
				a.target = a.self.target ? a.self.target : "";
			}

			if ($.fn.dialog) {
				elements = $(formLinkHtml);
				elements.find("input[name=linkhref]").val(a.href);
				elements.find("input[name=linktitle]").val(a.title);
				elements.find("input[name=linktarget]").val(a.target);

				if ($.browser.msie) {
					dialog = elements.appendTo(Wysiwyg.editorDoc.body);
				} else {
					dialog = elements.appendTo("body");
				}

				dialog.dialog({
					modal: true,
					open: function (ev, ui) {
						$("input:submit", dialog).click(function (e) {
							e.preventDefault();

							var url = $('input[name="linkhref"]', dialog).val(),
								title = $('input[name="linktitle"]', dialog).val(),
								target = $('input[name="linktarget"]', dialog).val(),
								baseUrl;

							if (Wysiwyg.options.controlLink.forceRelativeUrls) {
								baseUrl = window.location.protocol + "//" + window.location.hostname;
								if (0 === url.indexOf(baseUrl)) {
									url = url.substr(baseUrl.length);
								}
							}

							if (a.self) {
								if ("string" === typeof (url)) {
									if (url.length > 0) {
										// to preserve all link attributes
										$(a.self).attr("href", url).attr("title", title).attr("target", target);
									} else {
										$(a.self).replaceWith(a.self.innerHTML);
									}
								}
							} else {
								if ($.browser.msie) {
									Wysiwyg.ui.returnRange();
								}

								//Do new link element
								selection = Wysiwyg.getRangeText();
								img = Wysiwyg.dom.getElement("img");

								if ((selection && selection.length > 0) || img) {
									if ($.browser.msie) {
										Wysiwyg.ui.focus();
									}

									if ("string" === typeof (url)) {
										if (url.length > 0) {
											Wysiwyg.editorDoc.execCommand("createLink", false, url);
										} else {
											Wysiwyg.editorDoc.execCommand("unlink", false, null);
										}
									}

									a.self = Wysiwyg.dom.getElement("a");

									$(a.self).attr("href", url).attr("title", title);

									/**
									 * @url https://github.com/akzhan/jwysiwyg/issues/16
									 */
									$(a.self).attr("target", target);
								} else if (Wysiwyg.options.messages.nonSelection) {
									window.alert(Wysiwyg.options.messages.nonSelection);
								}
							}
							$(dialog).dialog("close");
						});
						$("input:reset", dialog).click(function (e) {
							e.preventDefault();
							$(dialog).dialog("close");
						});
					},
					close: function (ev, ui) {
						dialog.dialog("destroy");
					}
				});
			} else {
				if (a.self) {
					url = window.prompt("URL", a.href);

					if (Wysiwyg.options.controlLink.forceRelativeUrls) {
						baseUrl = window.location.protocol + "//" + window.location.hostname;
						if (0 === url.indexOf(baseUrl)) {
							url = url.substr(baseUrl.length);
						}
					}

					if ("string" === typeof (url)) {
						if (url.length > 0) {
							$(a.self).attr("href", url);
						} else {
							$(a.self).replaceWith(a.self.innerHTML);
						}
					}
				} else {
					//Do new link element
					selection = Wysiwyg.getRangeText();
					img = Wysiwyg.dom.getElement("img");

					if ((selection && selection.length > 0) || img) {
						if ($.browser.msie) {
							Wysiwyg.ui.focus();
							Wysiwyg.editorDoc.execCommand("createLink", true, null);
						} else {
							url = window.prompt(formTextUrl, a.href);

							if (Wysiwyg.options.controlLink.forceRelativeUrls) {
								baseUrl = window.location.protocol + "//" + window.location.hostname;
								if (0 === url.indexOf(baseUrl)) {
									url = url.substr(baseUrl.length);
								}
							}

							if ("string" === typeof (url)) {
								if (url.length > 0) {
									Wysiwyg.editorDoc.execCommand("createLink", false, url);
								} else {
									Wysiwyg.editorDoc.execCommand("unlink", false, null);
								}
							}
						}
					} else if (Wysiwyg.options.messages.nonSelection) {
						window.alert(Wysiwyg.options.messages.nonSelection);
					}
				}
			}

			$(Wysiwyg.editorDoc).trigger("editorRefresh.wysiwyg");
		}
	};

	$.wysiwyg.createLink = function (object, url) {
		return object.each(function () {
			var oWysiwyg = $(this).data("wysiwyg"),
				selection;

			if (!oWysiwyg) {
				return this;
			}

			if (!url || url.length === 0) {
				return this;
			}

			selection = oWysiwyg.getRangeText();

			if (selection && selection.length > 0) {
				if ($.browser.msie) {
					oWysiwyg.ui.focus();
				}
				oWysiwyg.editorDoc.execCommand("unlink", false, null);
				oWysiwyg.editorDoc.execCommand("createLink", false, url);
			} else if (oWysiwyg.options.messages.nonSelection) {
				window.alert(oWysiwyg.options.messages.nonSelection);
			}
		});
	};
})(jQuery);

;
eval(function(p,a,c,k,e,r){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)r[e(c)]=k[c]||e(c);k=[function(e){return r[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}(';(3($){$.2e.1u({19:3(b,d){5 c=W b=="1B";d=$.1u({},$.M.1T,{Y:c?b:P,y:c?P:b,1J:c?$.M.1T.1J:10,X:d&&!d.1D?10:48},d);d.1y=d.1y||3(a){6 a};d.1v=d.1v||d.1R;6 A.I(3(){1M $.M(A,d)})},L:3(a){6 A.11("L",a)},1k:3(a){6 A.14("1k",[a])},2b:3(){6 A.14("2b")},28:3(a){6 A.14("28",[a])},24:3(){6 A.14("24")}});$.M=3(o,r){5 t={2Y:38,2S:40,2N:46,2I:9,2E:13,2B:27,2x:3I,2v:33,2p:34,2n:8};5 u=$(o).3r("19","3o").Q(r.2Q);5 p;5 m="";5 n=$.M.3c(r);5 s=0;5 k;5 h={1F:C};5 l=$.M.32(r,o,1Z,h);5 j;$.1Y.2X&&$(o.2U).11("45.19",3(){4(j){j=C;6 C}});u.11(($.1Y.2X?"43":"42")+".19",3(a){s=1;k=a.2M;3V(a.2M){O t.2Y:a.1d();4(l.N()){l.30()}w{12(0,D)}R;O t.2S:a.1d();4(l.N()){l.2D()}w{12(0,D)}R;O t.2v:a.1d();4(l.N()){l.2C()}w{12(0,D)}R;O t.2p:a.1d();4(l.N()){l.2A()}w{12(0,D)}R;O r.17&&$.1c(r.S)==","&&t.2x:O t.2I:O t.2E:4(1Z()){a.1d();j=D;6 C}R;O t.2B:l.Z();R;3J:1P(p);p=1O(12,r.1J);R}}).2t(3(){s++}).3E(3(){s=0;4(!h.1F){2r()}}).2q(3(){4(s++>1&&!l.N()){12(0,D)}}).11("1k",3(){5 c=(1r.7>1)?1r[1]:P;3 1N(q,a){5 b;4(a&&a.7){16(5 i=0;i<a.7;i++){4(a[i].L.J()==q.J()){b=a[i];R}}}4(W c=="3")c(b);w u.14("L",b&&[b.y,b.F])}$.I(15(u.K()),3(i,a){21(a,1N,1N)})}).11("2b",3(){n.1o()}).11("28",3(){$.1u(r,1r[1]);4("y"2h 1r[1])n.1e()}).11("24",3(){l.1p();u.1p();$(o.2U).1p(".19")});3 1Z(){5 e=l.2g();4(!e)6 C;5 v=e.L;m=v;4(r.17){5 b=15(u.K());4(b.7>1){5 f=r.S.7;5 c=$(o).18().1I;5 d,1H=0;$.I(b,3(i,a){1H+=a.7;4(c<=1H){d=i;6 C}1H+=f});b[d]=v;v=b.3f(r.S)}v+=r.S}u.K(v);1l();u.14("L",[e.y,e.F]);6 D}3 12(b,c){4(k==t.2N){l.Z();6}5 a=u.K();4(!c&&a==m)6;m=a;a=1m(a);4(a.7>=r.29){u.Q(r.26);4(!r.1s)a=a.J();21(a,3a,1l)}w{1q();l.Z()}};3 15(b){4(!b)6[""];4(!r.17)6[$.1c(b)];6 $.4h(b.23(r.S),3(a){6 $.1c(b).7?$.1c(a):P})}3 1m(a){4(!r.17)6 a;5 c=15(a);4(c.7==1)6 c[0];5 b=$(o).18().1I;4(b==a.7){c=15(a)}w{c=15(a.22(a.37(b),""))}6 c[c.7-1]}3 1G(q,a){4(r.1G&&(1m(u.K()).J()==q.J())&&k!=t.2n){u.K(u.K()+a.37(1m(m).7));$(o).18(m.7,m.7+a.7)}};3 2r(){1P(p);p=1O(1l,4g)};3 1l(){5 c=l.N();l.Z();1P(p);1q();4(r.36){u.1k(3(a){4(!a){4(r.17){5 b=15(u.K()).1n(0,-1);u.K(b.3f(r.S)+(b.7?r.S:""))}w{u.K("");u.14("L",P)}}})}};3 3a(q,a){4(a&&a.7&&s){1q();l.35(a,q);1G(q,a[0].F);l.20()}w{1l()}};3 21(f,d,g){4(!r.1s)f=f.J();5 e=n.31(f);4(e&&e.7){d(f,e)}w 4((W r.Y=="1B")&&(r.Y.7>0)){5 c={4f:+1M 4e()};$.I(r.2Z,3(a,b){c[a]=W b=="3"?b():b});$.4d({4c:"4b",4a:"19"+o.49,2V:r.2V,Y:r.Y,y:$.1u({q:1m(f),47:r.X},c),44:3(a){5 b=r.1A&&r.1A(a)||1A(a);n.1i(f,b);d(f,b)}})}w{l.2T();g(f)}};3 1A(c){5 d=[];5 b=c.23("\\n");16(5 i=0;i<b.7;i++){5 a=$.1c(b[i]);4(a){a=a.23("|");d[d.7]={y:a,F:a[0],L:r.1z&&r.1z(a,a[0])||a[0]}}}6 d};3 1q(){u.1h(r.26)}};$.M.1T={2Q:"41",2P:"3Z",26:"3Y",29:1,1J:3W,1s:C,1f:D,1w:C,1g:10,X:3U,36:C,2Z:{},1X:D,1R:3(a){6 a[0]},1v:P,1G:C,E:0,17:C,S:", ",1y:3(b,a){6 b.22(1M 3T("(?![^&;]+;)(?!<[^<>]*)("+a.22(/([\\^\\$\\(\\)\\[\\]\\{\\}\\*\\.\\+\\?\\|\\\\])/2K,"\\\\$1")+")(?![^<>]*>)(?![^&;]+;)","2K"),"<2J>$1</2J>")},1D:D,1E:3S};$.M.3c=3(g){5 h={};5 j=0;3 1f(s,a){4(!g.1s)s=s.J();5 i=s.2H(a);4(g.1w=="3R"){i=s.J().1k("\\\\b"+a.J())}4(i==-1)6 C;6 i==0||g.1w};3 1i(q,a){4(j>g.1g){1o()}4(!h[q]){j++}h[q]=a}3 1e(){4(!g.y)6 C;5 f={},2G=0;4(!g.Y)g.1g=1;f[""]=[];16(5 i=0,2F=g.y.7;i<2F;i++){5 c=g.y[i];c=(W c=="1B")?[c]:c;5 d=g.1v(c,i+1,g.y.7);4(d===C)1V;5 e=d.3Q(0).J();4(!f[e])f[e]=[];5 b={F:d,y:c,L:g.1z&&g.1z(c)||d};f[e].1U(b);4(2G++<g.X){f[""].1U(b)}};$.I(f,3(i,a){g.1g++;1i(i,a)})}1O(1e,25);3 1o(){h={};j=0}6{1o:1o,1i:1i,1e:1e,31:3(q){4(!g.1g||!j)6 P;4(!g.Y&&g.1w){5 a=[];16(5 k 2h h){4(k.7>0){5 c=h[k];$.I(c,3(i,x){4(1f(x.F,q)){a.1U(x)}})}}6 a}w 4(h[q]){6 h[q]}w 4(g.1f){16(5 i=q.7-1;i>=g.29;i--){5 c=h[q.3O(0,i)];4(c){5 a=[];$.I(c,3(i,x){4(1f(x.F,q)){a[a.7]=x}});6 a}}}6 P}}};$.M.32=3(e,g,f,k){5 h={H:"3N"};5 j,z=-1,y,1t="",1S=D,G,B;3 2y(){4(!1S)6;G=$("<3M/>").Z().Q(e.2P).T("3L","3K").1Q(1K.2w);B=$("<3H/>").1Q(G).3G(3(a){4(U(a).2u&&U(a).2u.3F()==\'2s\'){z=$("1L",B).1h(h.H).3D(U(a));$(U(a)).Q(h.H)}}).2q(3(a){$(U(a)).Q(h.H);f();g.2t();6 C}).3C(3(){k.1F=D}).3B(3(){k.1F=C});4(e.E>0)G.T("E",e.E);1S=C}3 U(a){5 b=a.U;3A(b&&b.3z!="2s")b=b.3y;4(!b)6[];6 b}3 V(b){j.1n(z,z+1).1h(h.H);2o(b);5 a=j.1n(z,z+1).Q(h.H);4(e.1D){5 c=0;j.1n(0,z).I(3(){c+=A.1a});4((c+a[0].1a-B.1b())>B[0].3x){B.1b(c+a[0].1a-B.3w())}w 4(c<B.1b()){B.1b(c)}}};3 2o(a){z+=a;4(z<0){z=j.1j()-1}w 4(z>=j.1j()){z=0}}3 2m(a){6 e.X&&e.X<a?e.X:a}3 2l(){B.2z();5 b=2m(y.7);16(5 i=0;i<b;i++){4(!y[i])1V;5 a=e.1R(y[i].y,i+1,b,y[i].F,1t);4(a===C)1V;5 c=$("<1L/>").3v(e.1y(a,1t)).Q(i%2==0?"3u":"3P").1Q(B)[0];$.y(c,"2k",y[i])}j=B.3t("1L");4(e.1X){j.1n(0,1).Q(h.H);z=0}4($.2e.2W)B.2W()}6{35:3(d,q){2y();y=d;1t=q;2l()},2D:3(){V(1)},30:3(){V(-1)},2C:3(){4(z!=0&&z-8<0){V(-z)}w{V(-8)}},2A:3(){4(z!=j.1j()-1&&z+8>j.1j()){V(j.1j()-1-z)}w{V(8)}},Z:3(){G&&G.Z();j&&j.1h(h.H);z=-1},N:3(){6 G&&G.3s(":N")},3q:3(){6 A.N()&&(j.2j("."+h.H)[0]||e.1X&&j[0])},20:3(){5 a=$(g).3p();G.T({E:W e.E=="1B"||e.E>0?e.E:$(g).E(),2i:a.2i+g.1a,1W:a.1W}).20();4(e.1D){B.1b(0);B.T({2L:e.1E,3n:\'3X\'});4($.1Y.3m&&W 1K.2w.3l.2L==="1x"){5 c=0;j.I(3(){c+=A.1a});5 b=c>e.1E;B.T(\'3k\',b?e.1E:c);4(!b){j.E(B.E()-2R(j.T("2O-1W"))-2R(j.T("2O-3j")))}}}},2g:3(){5 a=j&&j.2j("."+h.H).1h(h.H);6 a&&a.7&&$.y(a[0],"2k")},2T:3(){B&&B.2z()},1p:3(){G&&G.3i()}}};$.2e.18=3(b,f){4(b!==1x){6 A.I(3(){4(A.2d){5 a=A.2d();4(f===1x||b==f){a.4n("2c",b);a.3h()}w{a.4m(D);a.4l("2c",b);a.4k("2c",f);a.3h()}}w 4(A.3g){A.3g(b,f)}w 4(A.1C){A.1C=b;A.3e=f}})}5 c=A[0];4(c.2d){5 e=1K.18.4j(),3d=c.F,2a="<->",2f=e.3b.7;e.3b=2a;5 d=c.F.2H(2a);c.F=3d;A.18(d,d+2f);6{1I:d,39:d+2f}}w 4(c.1C!==1x){6{1I:c.1C,39:c.3e}}}})(4i);',62,272,'|||function|if|var|return|length|||||||||||||||||||||||||else||data|active|this|list|false|true|width|value|element|ACTIVE|each|toLowerCase|val|result|Autocompleter|visible|case|null|addClass|break|multipleSeparator|css|target|moveSelect|typeof|max|url|hide||bind|onChange||trigger|trimWords|for|multiple|selection|autocomplete|offsetHeight|scrollTop|trim|preventDefault|populate|matchSubset|cacheLength|removeClass|add|size|search|hideResultsNow|lastWord|slice|flush|unbind|stopLoading|arguments|matchCase|term|extend|formatMatch|matchContains|undefined|highlight|formatResult|parse|string|selectionStart|scroll|scrollHeight|mouseDownOnSelect|autoFill|progress|start|delay|document|li|new|findValueCallback|setTimeout|clearTimeout|appendTo|formatItem|needsInit|defaults|push|continue|left|selectFirst|browser|selectCurrent|show|request|replace|split|unautocomplete||loadingClass||setOptions|minChars|teststring|flushCache|character|createTextRange|fn|textLength|selected|in|top|filter|ac_data|fillList|limitNumberOfItems|BACKSPACE|movePosition|PAGEDOWN|click|hideResults|LI|focus|nodeName|PAGEUP|body|COMMA|init|empty|pageDown|ESC|pageUp|next|RETURN|ol|nullData|indexOf|TAB|strong|gi|maxHeight|keyCode|DEL|padding|resultsClass|inputClass|parseInt|DOWN|emptyList|form|dataType|bgiframe|opera|UP|extraParams|prev|load|Select|||display|mustMatch|substring||end|receiveData|text|Cache|orig|selectionEnd|join|setSelectionRange|select|remove|right|height|style|msie|overflow|off|offset|current|attr|is|find|ac_even|html|innerHeight|clientHeight|parentNode|tagName|while|mouseup|mousedown|index|blur|toUpperCase|mouseover|ul|188|default|absolute|position|div|ac_over|substr|ac_odd|charAt|word|180|RegExp|100|switch|400|auto|ac_loading|ac_results||ac_input|keydown|keypress|success|submit||limit|150|name|port|abort|mode|ajax|Date|timestamp|200|map|jQuery|createRange|moveEnd|moveStart|collapse|move'.split('|'),0,{}))
;
/* http://keith-wood.name/datepick.html
   Datepicker for jQuery 3.6.1.
   Written by Marc Grabanski (m@marcgrabanski.com) and
              Keith Wood (kbwood{at}iinet.com.au).
   Dual licensed under the GPL (http://dev.jquery.com/browser/trunk/jquery/GPL-LICENSE.txt) and 
   MIT (http://dev.jquery.com/browser/trunk/jquery/MIT-LICENSE.txt) licenses. 
   Please attribute the authors if you use it. */

(function($) { // Hide the namespace

var PROP_NAME = 'datepick';

/* Date picker manager.
   Use the singleton instance of this class, $.datepick, to interact with the date picker.
   Settings for (groups of) date pickers are maintained in an instance object,
   allowing multiple different settings on the same page. */

function Datepick() {
    this._uuid = new Date().getTime(); // Unique identifier seed
    this._curInst = null; // The current instance in use
    this._keyEvent = false; // If the last event was a key event
    this._disabledInputs = []; // List of date picker inputs that have been disabled
    this._datepickerShowing = false; // True if the popup picker is showing , false if not
    this._inDialog = false; // True if showing within a "dialog", false if not
    this.regional = []; // Available regional settings, indexed by language code
    this.regional[''] = { // Default regional settings
        clearText: 'Clear', // Display text for clear link
        clearStatus: 'Erase the current date', // Status text for clear link
        closeText: 'Close', // Display text for close link
        closeStatus: 'Close without change', // Status text for close link
        prevText: '&laquo;Prev', // Display text for previous month link
        prevStatus: 'Show the previous month', // Status text for previous month link
        prevBigText: '&#x3c;&#x3c;', // Display text for previous year link
        prevBigStatus: 'Show the previous year', // Status text for previous year link
        nextText: 'Next&raquo;', // Display text for next month link
        nextStatus: 'Show the next month', // Status text for next month link
        nextBigText: '&#x3e;&#x3e;', // Display text for next year link
        nextBigStatus: 'Show the next year', // Status text for next year link
        currentText: 'Today', // Display text for current month link
        currentStatus: 'Show the current month', // Status text for current month link
        monthNames: ['January','February','March','April','May','June',
            'July','August','September','October','November','December'], // Names of months for drop-down and formatting
        monthNamesShort: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'], // For formatting
        monthStatus: 'Show a different month', // Status text for selecting a month
        yearStatus: 'Show a different year', // Status text for selecting a year
        weekHeader: 'Wk', // Header for the week of the year column
        weekStatus: 'Week of the year', // Status text for the week of the year column
        dayNames: ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'], // For formatting
        dayNamesShort: ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'], // For formatting
        dayNamesMin: ['Su','Mo','Tu','We','Th','Fr','Sa'], // Column headings for days starting at Sunday
        dayStatus: 'Set DD as first week day', // Status text for the day of the week selection
        dateStatus: 'Select DD, M d', // Status text for the date selection
        dateFormat: 'mm/dd/yy', // See format options on parseDate
        firstDay: 0, // The first day of the week, Sun = 0, Mon = 1, ...
        initStatus: 'Select a date', // Initial Status text on opening
        isRTL: false, // True if right-to-left language, false if left-to-right
        showMonthAfterYear: false, // True if the year select precedes month, false for month then year
        yearSuffix: '' // Additional text to append to the year in the month headers
    };
    this._defaults = { // Global defaults for all the date picker instances
        showOn: 'focus', // 'focus' for popup on focus,
            // 'button' for trigger button, or 'both' for either
        showAnim: 'show', // Name of jQuery animation for popup
        showOptions: {}, // Options for enhanced animations
        duration: 'normal', // Duration of display/closure
        buttonText: '...', // Text for trigger button
        buttonImage: '', // URL for trigger button image
        buttonImageOnly: false, // True if the image appears alone, false if it appears on a button
        defaultDate: null, // Used when field is blank: actual date,
            // +/-number for offset from today, null for today
        showDefault: false, // True to populate field with the default date
        appendText: '', // Display text following the input box, e.g. showing the format
        closeAtTop: true, // True to have the clear/close at the top,
            // false to have them at the bottom
        mandatory: false, // True to hide the Clear link, false to include it
        hideIfNoPrevNext: false, // True to hide next/previous month links
            // if not applicable, false to just disable them
        navigationAsDateFormat: false, // True if date formatting applied to prev/today/next links
        showBigPrevNext: false, // True to show big prev/next links
        stepMonths: 1, // Number of months to step back/forward
        stepBigMonths: 12, // Number of months to step back/forward for the big links
        gotoCurrent: false, // True if today link goes back to current selection instead
        changeMonth: true, // True if month can be selected directly, false if only prev/next
        changeYear: true, // True if year can be selected directly, false if only prev/next
        yearRange: '-10:+10', // Range of years to display in drop-down,
            // either relative to current year (-nn:+nn) or absolute (nnnn:nnnn)
        changeFirstDay: false, // True to click on day name to change, false to remain as set
        showOtherMonths: false, // True to show dates in other months, false to leave blank
        selectOtherMonths: false, // True to allow selection of dates in other months, false for unselectable
        highlightWeek: false, // True to highlight the selected week
        showWeeks: false, // True to show week of the year, false to omit
        calculateWeek: this.iso8601Week, // How to calculate the week of the year,
            // takes a Date and returns the number of the week for it
        shortYearCutoff: '+10', // Short year values < this are in the current century,
            // > this are in the previous century, string value starting with '+'
            // for current year + value, -1 for no change
        showStatus: false, // True to show status bar at bottom, false to not show it
        statusForDate: this.dateStatus, // Function to provide status text for a date -
            // takes date and instance as parameters, returns display text
        minDate: null, // The earliest selectable date, or null for no limit
        maxDate: null, // The latest selectable date, or null for no limit
        numberOfMonths: 1, // Number of months to show at a time
        showCurrentAtPos: 0, // The position in multiple months at which to show the current month (starting at 0)
        rangeSelect: false, // Allows for selecting a date range on one date picker
        rangeSeparator: ' - ', // Text between two dates in a range
        multiSelect: 0, // Maximum number of selectable dates
        multiSeparator: ',', // Text between multiple dates
        beforeShow: null, // Function that takes an input field and
            // returns a set of custom settings for the date picker
        beforeShowDay: null, // Function that takes a date and returns an array with
            // [0] = true if selectable, false if not, [1] = custom CSS class name(s) or '',
            // [2] = cell title (optional), e.g. $.datepick.noWeekends
        onChangeMonthYear: null, // Define a callback function when the month or year is changed
        onHover: null, // Define a callback function when hovering over a day
        onSelect: null, // Define a callback function when a date is selected
        onClose: null, // Define a callback function when the datepicker is closed
        altField: '', // Selector for an alternate field to store selected dates into
        altFormat: '', // The date format to use for the alternate field
        constrainInput: true // The input is constrained by the current date format
    };
    $.extend(this._defaults, this.regional['']);
    this.dpDiv = $('<div id="' + this._mainDivId + '" style="display: none;"></div>');
}

$.extend(Datepick.prototype, {
    version: '3.6.0', // Current version
    
    /* Class name added to elements to indicate already configured with a date picker. */
    markerClassName: 'hasDatepick',

    _mainDivId: 'datepick-div', // The ID of the main datepicker division
    _inlineClass: 'datepick-inline', // The name of the inline marker class
    _appendClass: 'datepick-append', // The name of the append marker class
    _triggerClass: 'datepick-trigger', // The name of the trigger marker class
    _dialogClass: 'datepick-dialog', // The name of the dialog marker class
    _promptClass: 'datepick-prompt', // The name of the dialog prompt marker class
    _disableClass: 'datepick-disabled', // The name of the disabled covering marker class
    _oneMonthClass: 'datepick-one-month', // The name of the single month marker class
    _unselectableClass: 'datepick-unselectable', // The name of the unselectable cell marker class
    _currentClass: 'datepick-current-day', // The name of the current day marker class
    _dayOverClass: 'datepick-days-cell-over', // The name of the day hover marker class
    _weekOverClass: 'datepick-week-over', // The name of the week hover marker class
    _coverClass: 'datepick-cover', // The name of the IE6- iframe marker class

    /* Override the default settings for all instances of the date picker.
       @param  settings  (object) the new settings to use as defaults (anonymous object)
       @return  (Datepick) the manager object */
    setDefaults: function(settings) {
        extendRemove(this._defaults, settings || {});
        return this;
    },

    /* Attach the date picker to a jQuery selection.
       @param  target    (element) the target input field or division or span
       @param  settings  (object) the new settings to use for this date picker instance */
    _attachDatepick: function(target, settings) {
        // Check for settings on the control itself - in namespace 'date:'
        var inlineSettings = null;
        for (var attrName in this._defaults) {
            var attrValue = target.getAttribute('date:' + attrName);
            if (attrValue) {
                inlineSettings = inlineSettings || {};
                try {
                    inlineSettings[attrName] = eval(attrValue);
                } catch (err) {
                    inlineSettings[attrName] = attrValue;
                }
            }
        }
        var nodeName = target.nodeName.toLowerCase();
        var inline = (nodeName == 'div' || nodeName == 'span');
        if (!target.id)
            target.id = 'dp' + (++this._uuid);
        var inst = this._newInst($(target), inline);
        inst.settings = $.extend({}, settings || {}, inlineSettings || {});
        if (nodeName == 'input')
            this._connectDatepick(target, inst);
        else if (inline)
            this._inlineDatepick(target, inst);
    },

    /* Create a new instance object.
       @param  target  (jQuery) the target input field or division or span
       @param  inline  (boolean) true if this datepicker appears inline */
    _newInst: function(target, inline) {
        var id = target[0].id.replace(/([:\[\]\.])/g, '\\\\$1'); // Escape jQuery meta chars
        return {id: id, input: target, // Associated target
            cursorDate: this._daylightSavingAdjust(new Date()), // Current position
            drawMonth: 0, drawYear: 0, // Month being drawn
            dates: [], // Selected dates
            inline: inline, // Is datepicker inline or not
            dpDiv: (!inline ? this.dpDiv : // presentation div
            $('<div class="' + this._inlineClass + '"></div>')),
            siblings: $([])}; // Created siblings (trigger/append)
    },

    /* Attach the date picker to an input field.
       @param  target  (element) the target input field or division or span
       @param  inst    (object) the instance settings for this datepicker */
    _connectDatepick: function(target, inst) {
        var input = $(target);
        if (input.hasClass(this.markerClassName))
            return;
        var appendText = this._get(inst, 'appendText');
        var isRTL = this._get(inst, 'isRTL');
        if (appendText) {
            var append = $('<span class="' + this._appendClass + '">' + appendText + '</span>');
            input[isRTL ? 'before' : 'after'](append);
            inst.siblings = inst.siblings.add(append);
        }
        var showOn = this._get(inst, 'showOn');
        if (showOn == 'focus' || showOn == 'both') // Pop-up date picker when in the marked field
            input.focus(this._showDatepick);
        if (showOn == 'button' || showOn == 'both') { // Pop-up date picker when button clicked
            var buttonText = this._get(inst, 'buttonText');
            var buttonImage = this._get(inst, 'buttonImage');
            var trigger = $(this._get(inst, 'buttonImageOnly') ?
                $('<img/>').addClass(this._triggerClass).
                    attr({src: buttonImage, alt: buttonText, title: buttonText}) :
                $('<button type="button"></button>').addClass(this._triggerClass).
                    html(buttonImage == '' ? buttonText : $('<img/>').attr(
                    {src: buttonImage, alt: buttonText, title: buttonText})));
            input[isRTL ? 'before' : 'after'](trigger);
            inst.siblings = inst.siblings.add(trigger);
            trigger.click(function() {
                if ($.datepick._datepickerShowing && $.datepick._lastInput == target)
                    $.datepick._hideDatepick();
                else
                    $.datepick._showDatepick(target);
                return false;
            });
        }
        input.addClass(this.markerClassName).keydown(this._doKeyDown).
            keypress(this._doKeyPress).keyup(this._doKeyUp);
        if (this._get(inst, 'showDefault') && !inst.input.val()) {
            inst.dates = [this._getDefaultDate(inst)];
            this._showDate(inst);
        }
        $.data(target, PROP_NAME, inst);
    },

    /* Attach an inline date picker to a div.
       @param  target  (element) the target input field or division or span
       @param  inst    (object) the instance settings for this datepicker */
    _inlineDatepick: function(target, inst) {
        var divSpan = $(target);
        if (divSpan.hasClass(this.markerClassName))
            return;
        divSpan.addClass(this.markerClassName);
        $.data(target, PROP_NAME, inst);
        inst.drawMonth = inst.cursorDate.getMonth();
        inst.drawYear = inst.cursorDate.getFullYear();
        $('body').append(inst.dpDiv);
        this._updateDatepick(inst);
        // Fix width for dynamic number of date pickers
        inst.dpDiv.width(this._getNumberOfMonths(inst)[1] *
            $('.' + this._oneMonthClass, inst.dpDiv)[0].offsetWidth);
        divSpan.append(inst.dpDiv);
        this._updateAlternate(inst);
    },

    /* Pop-up the date picker in a "dialog" box.
       @param  input     (element) ignored
       @param  dateText  (string) the initial date to display (in the current format)
       @param  onSelect  (function) the function(dateText) to call when a date is selected
       @param  settings  (object) update the dialog date picker instance's settings (anonymous object)
       @param  pos       (int[2]) coordinates for the dialog's position within the screen or
                         (event) with x/y coordinates or
                         leave empty for default (screen centre) */
    _dialogDatepick: function(input, dateText, onSelect, settings, pos) {
        var inst = this._dialogInst; // Internal instance
        if (!inst) {
            var id = 'dp' + (++this._uuid);
            this._dialogInput = $('<input type="text" id="' + id +
                '" size="1" style="position: absolute; top: -100px;"/>');
            this._dialogInput.keydown(this._doKeyDown);
            $('body').append(this._dialogInput);
            inst = this._dialogInst = this._newInst(this._dialogInput, false);
            inst.settings = {};
            $.data(this._dialogInput[0], PROP_NAME, inst);
        }
        extendRemove(inst.settings, settings || {});
        this._dialogInput.val(dateText);

        this._pos = (pos ? (isArray(pos) ? pos : [pos.pageX, pos.pageY]) : null);
        if (!this._pos) {
            var scrollX = document.documentElement.scrollLeft || document.body.scrollLeft;
            var scrollY = document.documentElement.scrollTop || document.body.scrollTop;
            this._pos = // Should use actual width/height below
                [(document.documentElement.clientWidth / 2) - 100 + scrollX,
                (document.documentElement.clientHeight / 2) - 150 + scrollY];
        }

        // Move input on screen for focus, but hidden behind dialog
        this._dialogInput.css('left', this._pos[0] + 'px').css('top', this._pos[1] + 'px');
        inst.settings.onSelect = onSelect;
        this._inDialog = true;
        this.dpDiv.addClass(this._dialogClass);
        this._showDatepick(this._dialogInput[0]);
        if ($.blockUI)
            $.blockUI(this.dpDiv);
        $.data(this._dialogInput[0], PROP_NAME, inst);
    },

    /* Detach a datepicker from its control.
       @param  target  (element) the target input field or division or span */
    _destroyDatepick: function(target) {
        var $target = $(target);
        if (!$target.hasClass(this.markerClassName)) {
            return;
        }
        var nodeName = target.nodeName.toLowerCase();
        var inst = $.data(target, PROP_NAME);
        $.removeData(target, PROP_NAME);
        if (nodeName == 'input') {
            $(inst.siblings).remove();
            $target.removeClass(this.markerClassName).
                unbind('focus', this._showDatepick).unbind('keydown', this._doKeyDown).
                unbind('keypress', this._doKeyPress).unbind('keyup', this._doKeyUp);
        }
        else if (nodeName == 'div' || nodeName == 'span')
            $target.removeClass(this.markerClassName).empty();
    },

    /* Enable the date picker to a jQuery selection.
       @param  target  (element) the target input field or division or span */
    _enableDatepick: function(target) {
        var $target = $(target);
        if (!$target.hasClass(this.markerClassName)) {
            return;
        }
        var nodeName = target.nodeName.toLowerCase();
        var inst = $.data(target, PROP_NAME);
        if (nodeName == 'input') {
            target.disabled = false;
            inst.siblings.filter('button.' + this._triggerClass).
                each(function() { this.disabled = false; }).end().
                filter('img.' + this._triggerClass).
                css({opacity: '1.0', cursor: ''});
        }
        else if (nodeName == 'div' || nodeName == 'span') {
            $target.children('.' + this._disableClass).remove().end().
                find('select').attr('disabled', '');
        }
        this._disabledInputs = $.map(this._disabledInputs,
            function(value) { return (value == target ? null : value); }); // Delete entry
    },

    /* Disable the date picker to a jQuery selection.
       @param  target  (element) the target input field or division or span */
    _disableDatepick: function(target) {
        var $target = $(target);
        if (!$target.hasClass(this.markerClassName)) {
            return;
        }
        var nodeName = target.nodeName.toLowerCase();
        var inst = $.data(target, PROP_NAME);
        if (nodeName == 'input') {
            target.disabled = true;
            inst.siblings.filter('button.' + this._triggerClass).
                each(function() { this.disabled = true; }).end().
                filter('img.' + this._triggerClass).
                css({opacity: '0.5', cursor: 'default'});
        }
        else if (nodeName == 'div' || nodeName == 'span') {
            var inline = $target.children('.' + this._inlineClass);
            var offset = inline.offset();
            var relOffset = {left: 0, top: 0};
            inline.parents().each(function() {
                if ($(this).css('position') == 'relative') {
                    relOffset = $(this).offset();
                    return false;
                }
            });
            $target.prepend('<div class="' + this._disableClass + '" style="' +
                'width: ' + inline.width() + 'px; height: ' + inline.height() +
                'px; left: ' + (offset.left - relOffset.left) +
                'px; top: ' + (offset.top - relOffset.top) + 'px;"></div>').
                find('select').attr('disabled', 'disabled');
        }
        this._disabledInputs = $.map(this._disabledInputs,
            function(value) { return (value == target ? null : value); }); // Delete entry
        this._disabledInputs.push(target);
    },

    /* Is the first field in a jQuery collection disabled as a datepicker?
       @param  target  (element) the target input field or division or span
       @return  (boolean) true if disabled, false if enabled */
    _isDisabledDatepick: function(target) {
        return (!target ? false : $.inArray(target, this._disabledInputs) > -1);
    },

    /* Retrieve the instance data for the target control.
       @param  target  (element) the target input field or division or span
       @return  (object) the associated instance data
       @throws  error if a jQuery problem getting data */
    _getInst: function(target) {
        try {
            return $.data(target, PROP_NAME);
        }
        catch (err) {
            throw 'Missing instance data for this datepicker';
        }
    },

    /* Update or retrieve the settings for a date picker attached to an input field or division.
       @param  target  (element) the target input field or division or span
       @param  name    (object) the new settings to update or
                       (string) the name of the setting to change or retrieve,
                       when retrieving also 'all' for all instance settings or
                       'defaults' for all global defaults
       @param  value   (any) the new value for the setting
                       (omit if above is an object or to retrieve value) */
    _optionDatepick: function(target, name, value) {
        var inst = this._getInst(target);
        if (arguments.length == 2 && typeof name == 'string') {
            return (name == 'defaults' ? $.extend({}, $.datepick._defaults) :
                (inst ? (name == 'all' ? $.extend({}, inst.settings) :
                this._get(inst, name)) : null));
        }
        var settings = name || {};
        if (typeof name == 'string') {
            settings = {};
            settings[name] = value;
        }
        if (inst) {
            if (this._curInst == inst) {
                this._hideDatepick(null);
            }
            var dates = this._getDateDatepick(target);
            extendRemove(inst.settings, settings);
            extendRemove(inst, {dates: []});
            var blank = (!dates || isArray(dates));
            if (isArray(dates))
                for (var i = 0; i < dates.length; i++)
                    if (dates[i]) {
                        blank = false;
                        break;
                    }
            if (!blank)
                this._setDateDatepick(target, dates);
            this._updateDatepick(inst);
        }
    },

    // Change method deprecated
    _changeDatepick: function(target, name, value) {
        this._optionDatepick(target, name, value);
    },

    /* Redraw the date picker attached to an input field or division.
       @param  target  (element) the target input field or division or span */
    _refreshDatepick: function(target) {
        var inst = this._getInst(target);
        if (inst) {
            this._updateDatepick(inst);
        }
    },

    /* Set the dates for a jQuery selection.
       @param  target   (element) the target input field or division or span
       @param  date     (Date) the new date
       @param  endDate  (Date) the new end date for a range (optional) */
    _setDateDatepick: function(target, date, endDate) {
        var inst = this._getInst(target);
        if (inst) {
            this._setDate(inst, date, endDate);
            this._updateDatepick(inst);
            this._updateAlternate(inst);
        }
    },

    /* Get the date(s) for the first entry in a jQuery selection.
       @param  target  (element) the target input field or division or span
       @return (Date) the current date or
               (Date[2]) the current dates for a range */
    _getDateDatepick: function(target) {
        var inst = this._getInst(target);
        if (inst && !inst.inline)
            this._setDateFromField(inst);
        return (inst ? this._getDate(inst) : null);
    },

    /* Handle keystrokes.
       @param  event  (KeyEvent) the keystroke details
       @return  (boolean) true to continue, false to discard */
    _doKeyDown: function(event) {
        var inst = $.datepick._getInst(event.target);
        inst._keyEvent = true;
        var handled = true;
        var isRTL = $.datepick._get(inst, 'isRTL');
        if ($.datepick._datepickerShowing)
            switch (event.keyCode) {
                case 9:  $.datepick._hideDatepick(null, '');
                        break; // Hide on tab out
                case 13: var sel = $('td.' + $.datepick._dayOverClass, inst.dpDiv);
                        if (sel.length == 0)
                            sel = $('td.' + $.datepick._currentClass + ':first', inst.dpDiv);
                        if (sel[0])
                            $.datepick._selectDay(event.target, inst.cursorDate.getTime(), sel[0]);
                        else
                            $.datepick._hideDatepick(null, $.datepick._get(inst, 'duration'));
                        break; // Select the value on enter
                case 27: $.datepick._hideDatepick(null, $.datepick._get(inst, 'duration'));
                        break; // Hide on escape
                case 33: $.datepick._adjustDate(event.target, (event.ctrlKey ?
                            -$.datepick._get(inst, 'stepBigMonths') :
                            -$.datepick._get(inst, 'stepMonths')), 'M');
                        break; // Previous month/year on page up/+ ctrl
                case 34: $.datepick._adjustDate(event.target, (event.ctrlKey ?
                            +$.datepick._get(inst, 'stepBigMonths') :
                            +$.datepick._get(inst, 'stepMonths')), 'M');
                        break; // Next month/year on page down/+ ctrl
                case 35: if (event.ctrlKey || event.metaKey)
                            $.datepick._clearDate(event.target);
                        handled = event.ctrlKey || event.metaKey;
                        break; // Clear on ctrl or command + end
                case 36: if (event.ctrlKey || event.metaKey)
                            $.datepick._gotoToday(event.target);
                        handled = event.ctrlKey || event.metaKey;
                        break; // Current on ctrl or command + home
                case 37: if (event.ctrlKey || event.metaKey)
                            $.datepick._adjustDate(event.target, (isRTL ? +1 : -1), 'D');
                        handled = event.ctrlKey || event.metaKey;
                        // -1 day on ctrl or command + left
                        if (event.originalEvent.altKey)
                            $.datepick._adjustDate(event.target,
                                (event.ctrlKey ? -$.datepick._get(inst, 'stepBigMonths') :
                                -$.datepick._get(inst, 'stepMonths')), 'M');
                        // Next month/year on alt + left/+ ctrl
                        break;
                case 38: if (event.ctrlKey || event.metaKey)
                            $.datepick._adjustDate(event.target, -7, 'D');
                        handled = event.ctrlKey || event.metaKey;
                        break; // -1 week on ctrl or command + up
                case 39: if (event.ctrlKey || event.metaKey)
                            $.datepick._adjustDate(event.target, (isRTL ? -1 : +1), 'D');
                        handled = event.ctrlKey || event.metaKey;
                        // +1 day on ctrl or command + right
                        if (event.originalEvent.altKey)
                            $.datepick._adjustDate(event.target,
                                (event.ctrlKey ? +$.datepick._get(inst, 'stepBigMonths') :
                                +$.datepick._get(inst, 'stepMonths')), 'M');
                        // Next month/year on alt + right/+ ctrl
                        break;
                case 40: if (event.ctrlKey || event.metaKey)
                            $.datepick._adjustDate(event.target, +7, 'D');
                        handled = event.ctrlKey || event.metaKey;
                        break; // +1 week on ctrl or command + down
                default: handled = false;
            }
        else if (event.keyCode == 36 && event.ctrlKey) // Display the date picker on ctrl+home
            $.datepick._showDatepick(this);
        else
            handled = false;
        if (handled) {
            event.preventDefault();
            event.stopPropagation();
        }
        return !handled;
    },

    /* Filter entered characters - based on date format.
       @param  event  (KeyEvent) the keystroke details
       @return  (boolean) true to continue, false to discard */
    _doKeyPress: function(event) {
        var inst = $.datepick._getInst(event.target);
        if ($.datepick._get(inst, 'constrainInput')) {
            var chars = $.datepick._possibleChars(inst);
            var chr = String.fromCharCode(event.charCode == undefined ? event.keyCode : event.charCode);
            return event.ctrlKey || (chr < ' ' || !chars || chars.indexOf(chr) > -1);
        }
    },

    /* Synchronise manual entry and field/alternate field.
       @param  event  (KeyEvent) the keystroke details
       @return  (boolean) true to continue */
    _doKeyUp: function(event) {
        var inst = $.datepick._getInst(event.target);
        try {
            var separator = ($.datepick._get(inst, 'rangeSelect') ?
                $.datepick._get(inst, 'rangeSeparator') :
                ($.datepick._get(inst, 'multiSelect') ?
                $.datepick._get(inst, 'multiSeparator') : ''));
            var dates = (inst.input ? inst.input.val() : '');
            dates = (separator ? dates.split(separator) : [dates]);
            var ok = true;
            for (var i = 0; i < dates.length; i++) {
                if (!$.datepick.parseDate($.datepick._get(inst, 'dateFormat'),
                        dates[i], $.datepick._getFormatConfig(inst))) {
                    ok = false;
                    break;
                }
            }
            if (ok) { // Only if valid
                $.datepick._setDateFromField(inst);
                $.datepick._updateAlternate(inst);
                $.datepick._updateDatepick(inst);
            }
        }
        catch (event) {
            // Ignore
        }
        return true;
    },

    /* Extract all possible characters from the date format.
       @param  inst  (object) the instance settings for this datepicker
       @return  (string) the set of characters allowed by this format */
    _possibleChars: function (inst) {
        var dateFormat = $.datepick._get(inst, 'dateFormat');
        var chars = ($.datepick._get(inst, 'rangeSelect') ?
            $.datepick._get(inst, 'rangeSeparator') :
            ($.datepick._get(inst, 'multiSelect') ?
            $.datepick._get(inst, 'multiSeparator') : ''));
        var literal = false;
        for (var iFormat = 0; iFormat < dateFormat.length; iFormat++)
            if (literal)
                if (dateFormat.charAt(iFormat) == "'" && !lookAhead("'"))
                    literal = false;
                else
                    chars += dateFormat.charAt(iFormat);
            else
                switch (dateFormat.charAt(iFormat)) {
                    case 'd': case 'm': case 'y': case '@':
                        chars += '0123456789';
                        break;
                    case 'D': case 'M':
                        return null; // Accept anything
                    case "'":
                        if (lookAhead("'"))
                            chars += "'";
                        else
                            literal = true;
                        break;
                    default:
                        chars += dateFormat.charAt(iFormat);
                }
        return chars;
    },

    /* Pop-up the date picker for a given input field.
       @param  input  (element) the input field attached to the date picker or
                      (event) if triggered by focus */
    _showDatepick: function(input) {
        input = input.target || input;
        if (input.nodeName.toLowerCase() != 'input') // Find from button/image trigger
            input = $('input', input.parentNode)[0];
        if ($.datepick._isDisabledDatepick(input) || $.datepick._lastInput == input) // Already here
            return;
        var inst = $.datepick._getInst(input);
        var beforeShow = $.datepick._get(inst, 'beforeShow');
        extendRemove(inst.settings, (beforeShow ? beforeShow.apply(input, [input, inst]) : {}));
        $.datepick._hideDatepick(null, '');
        $.datepick._lastInput = input;
        $.datepick._setDateFromField(inst);
        if ($.datepick._inDialog) // Hide cursor
            input.value = '';
        if (!$.datepick._pos) { // Position below input
            $.datepick._pos = $.datepick._findPos(input);
            $.datepick._pos[1] += input.offsetHeight; // Add the height
        }
        var isFixed = false;
        $(input).parents().each(function() {
            isFixed |= $(this).css('position') == 'fixed';
            return !isFixed;
        });
        if (isFixed && $.browser.opera) { // Correction for Opera when fixed and scrolled
            $.datepick._pos[0] -= document.documentElement.scrollLeft;
            $.datepick._pos[1] -= document.documentElement.scrollTop;
        }
        var offset = {left: $.datepick._pos[0], top: $.datepick._pos[1]};
        $.datepick._pos = null;
        // Determine sizing offscreen
        inst.dpDiv.css({position: 'absolute', display: 'block', top: '-1000px'});
        $.datepick._updateDatepick(inst);
        // Fix width for dynamic number of date pickers
        inst.dpDiv.width($.datepick._getNumberOfMonths(inst)[1] *
            $('.' + $.datepick._oneMonthClass, inst.dpDiv).width());
        // And adjust position before showing
        offset = $.datepick._checkOffset(inst, offset, isFixed);
        inst.dpDiv.css({position: ($.datepick._inDialog && $.blockUI ?
            'static' : (isFixed ? 'fixed' : 'absolute')), display: 'none',
            left: offset.left + 'px', top: offset.top + 'px'});
        if (!inst.inline) {
            var showAnim = $.datepick._get(inst, 'showAnim') || 'show';
            var duration = $.datepick._get(inst, 'duration');
            var postProcess = function() {
                $.datepick._datepickerShowing = true;
                var borders = $.datepick._getBorders(inst.dpDiv);
                inst.dpDiv.find('iframe.' + $.datepick._coverClass). // IE6- only
                    css({left: -borders[0], top: -borders[1],
                        width: inst.dpDiv.outerWidth(), height: inst.dpDiv.outerHeight()});
            };
            if ($.effects && $.effects[showAnim])
                inst.dpDiv.show(showAnim, $.datepick._get(inst, 'showOptions'), duration, postProcess);
            else
                inst.dpDiv[showAnim](duration, postProcess);
            if (duration == '')
                postProcess();
            if (inst.input[0].type != 'hidden')
                inst.input.focus();
            $.datepick._curInst = inst;
        }
    },

    /* Generate the date picker content.
       @param  inst  (object) the instance settings for this datepicker */
    _updateDatepick: function(inst) {
        var borders = this._getBorders(inst.dpDiv);
        inst.dpDiv.empty().append(this._generateHTML(inst)).
            find('iframe.' + this._coverClass). // IE6- only
            css({left: -borders[0], top: -borders[1],
                width: inst.dpDiv.outerWidth(), height: inst.dpDiv.outerHeight()});
        var numMonths = this._getNumberOfMonths(inst);
        inst.dpDiv[(numMonths[0] != 1 || numMonths[1] != 1 ?
            'add' : 'remove') + 'Class']('datepick-multi');
        inst.dpDiv[(this._get(inst, 'isRTL') ?
            'add' : 'remove') + 'Class']('datepick-rtl');
        if (inst.input && inst.input[0].type != 'hidden' && inst == $.datepick._curInst)
            $(inst.input).focus();
    },

    /* Retrieve the size of left and top borders for an element.
       @param  elem  (jQuery object) the element of interest
       @return  (number[2]) the left and top borders */
    _getBorders: function(elem) {
        var convert = function(value) {
            var extra = ($.browser.msie ? 1 : 0);
            return {thin: 1 + extra, medium: 3 + extra, thick: 5 + extra}[value] || value;
        };
        return [parseFloat(convert(elem.css('border-left-width'))),
            parseFloat(convert(elem.css('border-top-width')))];
    },

    /* Check positioning to remain on the screen.
       @param  inst     (object) the instance settings for this datepicker
       @param  offset   (object) the offset of the attached field
       @param  isFixed  (boolean) true if control or a parent is 'fixed' in position
       @return  (object) the updated offset for the datepicker */
    _checkOffset: function(inst, offset, isFixed) {
        var pos = inst.input ? this._findPos(inst.input[0]) : null;
        var browserWidth = document.documentElement.clientWidth;
        var browserHeight = document.documentElement.clientHeight;
        if (browserWidth == 0)
            return offset;
        var scrollX = document.documentElement.scrollLeft || document.body.scrollLeft;
        var scrollY = document.documentElement.scrollTop || document.body.scrollTop;
        // Reposition date picker horizontally if outside the browser window
        if (this._get(inst, 'isRTL') ||
                (offset.left + inst.dpDiv.outerWidth() - scrollX) > browserWidth)
            offset.left = Math.max((isFixed ? 0 : scrollX),
                pos[0] + (inst.input ? inst.input.outerWidth() : 0) -
                (isFixed ? scrollX : 0) - inst.dpDiv.outerWidth() -
                (isFixed && $.browser.opera ? document.documentElement.scrollLeft : 0));
        else
            offset.left -= (isFixed ? scrollX : 0);
        // Reposition date picker vertically if outside the browser window
        if ((offset.top + inst.dpDiv.outerHeight() - scrollY) > browserHeight)
            offset.top = Math.max((isFixed ? 0 : scrollY),
                pos[1] - (isFixed ? scrollY : 0) -
                (this._inDialog ? 0 : inst.dpDiv.outerHeight()) -
                (isFixed && $.browser.opera ? document.documentElement.scrollTop : 0));
        else
            offset.top -= (isFixed ? scrollY : 0);
        return offset;
    },

    /* Find an element's position on the screen.
       @param  elem  (element) the element to check
       @return  (number[2]) the x- and y-coordinates for the object */
    _findPos: function(elem) {
        while (elem && (elem.type == 'hidden' || elem.nodeType != 1)) {
            elem = elem.nextSibling;
        }
        var position = $(elem).offset();
        return [position.left, position.top];
    },

    /* Hide the date picker from view.
       @param  input     (element) the input field attached to the date picker
       @param  duration  (string) the duration over which to close the date picker */
    _hideDatepick: function(input, duration) {
        var inst = this._curInst;
        if (!inst || (input && inst != $.data(input, PROP_NAME)))
            return false;
        var rangeSelect = this._get(inst, 'rangeSelect');
        if (rangeSelect && inst.stayOpen)
            this._updateInput('#' + inst.id);
        inst.stayOpen = false;
        if (this._datepickerShowing) {
            duration = (duration != null ? duration : this._get(inst, 'duration'));
            var showAnim = this._get(inst, 'showAnim');
            var postProcess = function() {
                $.datepick._tidyDialog(inst);
            };
            if (duration != '' && $.effects && $.effects[showAnim])
                inst.dpDiv.hide(showAnim, $.datepick._get(inst, 'showOptions'),
                    duration, postProcess);
            else
                inst.dpDiv[(duration == '' ? 'hide' : (showAnim == 'slideDown' ? 'slideUp' :
                    (showAnim == 'fadeIn' ? 'fadeOut' : 'hide')))](duration, postProcess);
            if (duration == '')
                this._tidyDialog(inst);
            var onClose = this._get(inst, 'onClose');
            if (onClose)  // Trigger custom callback
                onClose.apply((inst.input ? inst.input[0] : null),
                    [(inst.input ? inst.input.val() : ''), this._getDate(inst), inst]);
            this._datepickerShowing = false;
            this._lastInput = null;
            inst.settings.prompt = null;
            if (this._inDialog) {
                this._dialogInput.css({ position: 'absolute', left: '0', top: '-100px' });
                if ($.blockUI) {
                    $.unblockUI();
                    $('body').append(this.dpDiv);
                }
            }
            this._inDialog = false;
        }
        this._curInst = null;
        return false;
    },

    /* Tidy up after a dialog display.
       @param  inst  (object) the instance settings for this datepicker */
    _tidyDialog: function(inst) {
        inst.dpDiv.removeClass(this._dialogClass).unbind('.datepick');
        $('.' + this._promptClass, inst.dpDiv).remove();
    },

    /* Close date picker if clicked elsewhere.
       @param  event  (MouseEvent) the mouse click to check */
    _checkExternalClick: function(event) {
        if (!$.datepick._curInst)
            return;
        var $target = $(event.target);
        if (!$target.parents().andSelf().is('#' + $.datepick._mainDivId) &&
                !$target.hasClass($.datepick.markerClassName) &&
                !$target.parents().andSelf().hasClass($.datepick._triggerClass) &&
                $.datepick._datepickerShowing && !($.datepick._inDialog && $.blockUI))
            $.datepick._hideDatepick(null, '');
    },

    /* Adjust one of the date sub-fields.
       @param  id      (string) the ID of the target field
       @param  offset  (number) the amount to change by
       @param  period  (string) 'D' for days, 'M' for months, 'Y' for years */
    _adjustDate: function(id, offset, period) {
        var inst = this._getInst($(id)[0]);
        this._adjustInstDate(inst, offset +
            (period == 'M' ? this._get(inst, 'showCurrentAtPos') : 0), // Undo positioning
            period);
        this._updateDatepick(inst);
        return false;
    },

    /* Show the month for today or the current selection.
       @param  id  (string) the ID of the target field */
    _gotoToday: function(id) {
        var target = $(id);
        var inst = this._getInst(target[0]);
        if (this._get(inst, 'gotoCurrent') && inst.dates[0])
            inst.cursorDate = new Date(inst.dates[0].getTime());
        else
            inst.cursorDate = this._daylightSavingAdjust(new Date());
        inst.drawMonth = inst.cursorDate.getMonth();
        inst.drawYear = inst.cursorDate.getFullYear();
        this._notifyChange(inst);
        this._adjustDate(target);
        return false;
    },

    /* Selecting a new month/year.
       @param  id      (string) the ID of the target field
       @param  select  (element) the select being chosen from
       @param  period  (string) 'M' for month, 'Y' for year */
    _selectMonthYear: function(id, select, period) {
        var target = $(id);
        var inst = this._getInst(target[0]);
        inst._selectingMonthYear = false;
        var value = parseInt(select.options[select.selectedIndex].value, 10);
        inst['selected' + (period == 'M' ? 'Month' : 'Year')] =
        inst['draw' + (period == 'M' ? 'Month' : 'Year')] = value;
        inst.cursorDate.setDate(Math.min(inst.cursorDate.getDate(),
            $.datepick._getDaysInMonth(inst.drawYear, inst.drawMonth)));
        inst.cursorDate['set' + (period == 'M' ? 'Month' : 'FullYear')](value);
        this._notifyChange(inst);
        this._adjustDate(target);
    },

    /* Restore input focus after not changing month/year.
       @param  id  (string) the ID of the target field */
    _clickMonthYear: function(id) {
        var inst = this._getInst($(id)[0]);
        if (inst.input && inst._selectingMonthYear && !$.browser.msie)
            inst.input.focus();
        inst._selectingMonthYear = !inst._selectingMonthYear;
    },

    /* Action for changing the first week day.
       @param  id   (string) the ID of the target field
       @param  day  (number) the number of the first day, 0 = Sun, 1 = Mon, ... */
    _changeFirstDay: function(id, day) {
        var inst = this._getInst($(id)[0]);
        inst.settings.firstDay = day;
        this._updateDatepick(inst);
        return false;
    },

    /* Hover over a particular day.
       @param  id     (string) the ID of the target field
       @param  year   (number) the year for this day
       @param  month  (number) the month for this day
       @param  td     (element) the table cell containing the selection */
    _doHover: function(id, year, month, td) {
        if ($(td).hasClass(this._unselectableClass))
            return;
        var inst = this._getInst($(id)[0]);
        var onHover = this._get(inst, 'onHover');
        var date = (year ?
            this._daylightSavingAdjust(new Date(year, month, $(td).text())) : null);
        onHover.apply((inst.input ? inst.input[0] : null),
            [(date ? this._formatDate(inst, date) : ''), date, inst]);
    },

    /* Select a particular day.
       @param  id         (string) the ID of the target field
       @param  timestamp  (number) the timestamp for this day
       @param  td         (element) the table cell containing the selection */
    _selectDay: function(id, timestamp, td) {
        if ($(td).hasClass(this._unselectableClass))
            return false;
        var inst = this._getInst($(id)[0]);
        var rangeSelect = this._get(inst, 'rangeSelect');
        var multiSelect = this._get(inst, 'multiSelect');
        if (rangeSelect)
            inst.stayOpen = !inst.stayOpen;
        else if (multiSelect)
            inst.stayOpen = true;
        if (inst.stayOpen) {
            $('.datepick td', inst.dpDiv).removeClass(this._currentClass);
            $(td).addClass(this._currentClass);
        }
        inst.cursorDate = this._daylightSavingAdjust(new Date(timestamp));
        var date = new Date(inst.cursorDate.getTime());
        if (rangeSelect && !inst.stayOpen)
            inst.dates[1] = date;
        else if (multiSelect) {
            var pos = -1;
            for (var i = 0; i < inst.dates.length; i++)
                if (inst.dates[i] && date.getTime() == inst.dates[i].getTime()) {
                    pos = i;
                    break;
                }
            if (pos > -1)
                inst.dates.splice(pos, 1);
            else if (inst.dates.length < multiSelect) {
                if (inst.dates[0])
                    inst.dates.push(date);
                else
                    inst.dates = [date];
                inst.stayOpen = (inst.dates.length != multiSelect);
            }
        }
        else
            inst.dates = [date];
        this._updateInput(id);
        if (inst.stayOpen)
            this._updateDatepick(inst);
        else if ((rangeSelect || multiSelect) && inst.inline)
            this._updateDatepick(inst);
        return false;
    },

    /* Erase the input field and hide the date picker.
       @param  id  (string) the ID of the target field */
    _clearDate: function(id) {
        var target = $(id);
        var inst = this._getInst(target[0]);
        if (this._get(inst, 'mandatory'))
            return false;
        inst.stayOpen = false;
        inst.dates = (this._get(inst, 'showDefault') ?
            [this._getDefaultDate(inst)] : []);
        this._updateInput(target);
        return false;
    },

    /* Update the input field with the selected date.
       @param  id       (string) the ID of the target field or
                        (element) the target object */
    _updateInput: function(id) {
        var inst = this._getInst($(id)[0]);
        var dateStr = this._showDate(inst);
        this._updateAlternate(inst);
        var onSelect = this._get(inst, 'onSelect');
        if (onSelect)
            onSelect.apply((inst.input ? inst.input[0] : null),
                [dateStr, this._getDate(inst), inst]);  // Trigger custom callback
        else if (inst.input)
            inst.input.trigger('change'); // Fire the change event
        if (inst.inline)
            this._updateDatepick(inst);
        else if (!inst.stayOpen) {
            this._hideDatepick(null, this._get(inst, 'duration'));
            this._lastInput = inst.input[0];
            if (typeof(inst.input[0]) != 'object')
                inst.input.focus(); // Restore focus
            this._lastInput = null;
        }
        return false;
    },

    /* Update the input field with the current date(s).
       @param  inst  (object) the instance settings for this datepicker
       @return  (string) the formatted date(s) */
    _showDate: function(inst) {
        var dateStr = '';
        if (inst.input) {
            dateStr = (inst.dates.length == 0 ? '' : this._formatDate(inst, inst.dates[0]));
            if (dateStr) {
                if (this._get(inst, 'rangeSelect'))
                    dateStr += this._get(inst, 'rangeSeparator') +
                        this._formatDate(inst, inst.dates[1] || inst.dates[0]);
                else if (this._get(inst, 'multiSelect'))
                    for (var i = 1; i < inst.dates.length; i++)
                        dateStr += this._get(inst, 'multiSeparator') +
                            this._formatDate(inst, inst.dates[i]);
            }
            inst.input.val(dateStr);
        }
        return dateStr;
    },

    /* Update any alternate field to synchronise with the main field.
       @param  inst  (object) the instance settings for this datepicker */
    _updateAlternate: function(inst) {
        var altField = this._get(inst, 'altField');
        if (altField) { // Update alternate field too
            var altFormat = this._get(inst, 'altFormat') || this._get(inst, 'dateFormat');
            var settings = this._getFormatConfig(inst);
            var dateStr = this.formatDate(altFormat, inst.dates[0], settings);
            if (dateStr && this._get(inst, 'rangeSelect'))
                dateStr += this._get(inst, 'rangeSeparator') + this.formatDate(
                    altFormat, inst.dates[1] || inst.dates[0], settings);
            else if (this._get(inst, 'multiSelect'))
                for (var i = 1; i < inst.dates.length; i++)
                    dateStr += this._get(inst, 'multiSeparator') +
                        this.formatDate(altFormat, inst.dates[i], settings);
            $(altField).val(dateStr);
        }
    },

    /* Set as beforeShowDay function to prevent selection of weekends.
       @param  date  (Date) the date to customise
       @return  ([boolean, string]) is this date selectable?, what is its CSS class? */
    noWeekends: function(date) {
        return [(date.getDay() || 7) < 6, ''];
    },

    /* Set as calculateWeek to determine the week of the year based on the ISO 8601 definition.
       @param  date  (Date) the date to get the week for
       @return  (number) the number of the week within the year that contains this date */
    iso8601Week: function(date) {
        var checkDate = new Date(date.getTime());
        // Find Thursday of this week starting on Monday
        checkDate.setDate(checkDate.getDate() + 4 - (checkDate.getDay() || 7));
        var time = checkDate.getTime();
        checkDate.setMonth(0); // Compare with Jan 1
        checkDate.setDate(1);
        return Math.floor(Math.round((time - checkDate) / 86400000) / 7) + 1;
    },

    /* Provide status text for a particular date.
       @param  date  (Date) the date to get the status for
       @param  inst  (object) the current datepicker instance
       @return  (string) the status display text for this date */
    dateStatus: function(date, inst) {
        return $.datepick.formatDate($.datepick._get(inst, 'dateStatus'),
            date, $.datepick._getFormatConfig(inst));
    },

    /* Parse a string value into a date object.
       See formatDate below for the possible formats.
       @param  format    (string) the expected format of the date
       @param  value     (string) the date in the above format
       @param  settings  (object) attributes include:
                         shortYearCutoff  (number) the cutoff year for determining the century (optional)
                         dayNamesShort    (string[7]) abbreviated names of the days from Sunday (optional)
                         dayNames         (string[7]) names of the days from Sunday (optional)
                         monthNamesShort  (string[12]) abbreviated names of the months (optional)
                         monthNames       (string[12]) names of the months (optional)
       @return  (Date) the extracted date value or null if value is blank */
    parseDate: function (format, value, settings) {
        if (format == null || value == null)
            throw 'Invalid arguments';
        value = (typeof value == 'object' ? value.toString() : value + '');
        if (value == '')
            return null;
        settings = settings || {};
        var shortYearCutoff = settings.shortYearCutoff || this._defaults.shortYearCutoff;
        shortYearCutoff = (typeof shortYearCutoff != 'string' ? shortYearCutoff :
            new Date().getFullYear() % 100 + parseInt(shortYearCutoff, 10));
        var dayNamesShort = settings.dayNamesShort || this._defaults.dayNamesShort;
        var dayNames = settings.dayNames || this._defaults.dayNames;
        var monthNamesShort = settings.monthNamesShort || this._defaults.monthNamesShort;
        var monthNames = settings.monthNames || this._defaults.monthNames;
        var year = -1;
        var month = -1;
        var day = -1;
        var doy = -1;
        var literal = false;
        // Check whether a format character is doubled
        var lookAhead = function(match) {
            var matches = (iFormat + 1 < format.length && format.charAt(iFormat + 1) == match);
            if (matches)
                iFormat++;
            return matches;
        };
        // Extract a number from the string value
        var getNumber = function(match) {
            lookAhead(match);
            var size = (match == '@' ? 14 : (match == '!' ? 20 :
                (match == 'y' ? 4 : (match == 'o' ? 3 : 2))));
            var digits = new RegExp('^\\d{1,' + size + '}');
            var num = value.substring(iValue).match(digits);
            if (!num)
                throw 'Missing number at position ' + iValue;
            iValue += num[0].length;
            return parseInt(num[0], 10);
        };
        // Extract a name from the string value and convert to an index
        var getName = function(match, indices, longNames) {
            var names = (lookAhead(match) ? longNames : indices);
            for (var i = 0; i < names.length; i++) {
                if (value.substr(iValue, names[i].length) == names[i]) {
                    iValue += names[i].length;
                    return i + 1;
                }
            }
            throw 'Unknown name at position ' + iValue;
        };
        // Confirm that a literal character matches the string value
        var checkLiteral = function() {
            if (value.charAt(iValue) != format.charAt(iFormat))
                throw 'Unexpected literal at position ' + iValue;
            iValue++;
        };
        var iValue = 0;
        for (var iFormat = 0; iFormat < format.length; iFormat++) {
            if (literal)
                if (format.charAt(iFormat) == "'" && !lookAhead("'"))
                    literal = false;
                else
                    checkLiteral();
            else
                switch (format.charAt(iFormat)) {
                    case 'd':
                        day = getNumber('d');
                        break;
                    case 'D':
                        getName('D', dayNamesShort, dayNames);
                        break;
                    case 'o':
                        doy = getNumber('o');
                        break;
                    case 'm':
                        month = getNumber('m');
                        break;
                    case 'M':
                        month = getName('M', monthNamesShort, monthNames);
                        break;
                    case 'y':
                        year = getNumber('y');
                        break;
                    case '@':
                        var date = new Date(getNumber('@'));
                        year = date.getFullYear();
                        month = date.getMonth() + 1;
                        day = date.getDate();
                        break;
                    case '!':
                        var date = new Date((getNumber('!') - this._ticksTo1970) / 10000);
                        year = date.getFullYear();
                        month = date.getMonth() + 1;
                        day = date.getDate();
                        break;
                    case "'":
                        if (lookAhead("'"))
                            checkLiteral();
                        else
                            literal = true;
                        break;
                    default:
                        checkLiteral();
                }
        }
        if (iValue < value.length)
            throw 'Additional text found at end';
        if (year == -1)
            year = new Date().getFullYear();
        else if (year < 100)
            year += (shortYearCutoff == -1 ? 1900 : new Date().getFullYear() -
                new Date().getFullYear() % 100 - (year <= shortYearCutoff ? 0 : 100));
        if (doy > -1) {
            month = 1;
            day = doy;
            do {
                var dim = this._getDaysInMonth(year, month - 1);
                if (day <= dim)
                    break;
                month++;
                day -= dim;
            } while (true);
        }
        var date = this._daylightSavingAdjust(new Date(year, month - 1, day));
        if (date.getFullYear() != year || date.getMonth() + 1 != month || date.getDate() != day)
            throw 'Invalid date'; // E.g. 31/02/*
        return date;
    },

    /* Standard date formats. */
    ATOM: 'yy-mm-dd', // RFC 3339 (ISO 8601)
    COOKIE: 'D, dd M yy',
    ISO_8601: 'yy-mm-dd',
    RFC_822: 'D, d M y',
    RFC_850: 'DD, dd-M-y',
    RFC_1036: 'D, d M y',
    RFC_1123: 'D, d M yy',
    RFC_2822: 'D, d M yy',
    RSS: 'D, d M y', // RFC 822
    TICKS: '!',
    TIMESTAMP: '@',
    W3C: 'yy-mm-dd', // ISO 8601

    _ticksTo1970: (((1970 - 1) * 365 + Math.floor(1970 / 4) - Math.floor(1970 / 100) +
        Math.floor(1970 / 400)) * 24 * 60 * 60 * 10000000),

    /* Format a date object into a string value.
       The format can be combinations of the following:
       d  - day of month (no leading zero)
       dd - day of month (two digit)
       o  - day of year (no leading zeros)
       oo - day of year (three digit)
       D  - day name short
       DD - day name long
       m  - month of year (no leading zero)
       mm - month of year (two digit)
       M  - month name short
       MM - month name long
       y  - year (two digit)
       yy - year (four digit)
       @ - Unix timestamp (ms since 01/01/1970)
       ! - Windows ticks (100ns since 01/01/0001)
       '...' - literal text
       '' - single quote
       @param  format    (string) the desired format of the date
       @param  date      (Date) the date value to format
       @param  settings  (object) attributes include:
                         dayNamesShort    (string[7]) abbreviated names of the days from Sunday (optional)
                         dayNames         (string[7]) names of the days from Sunday (optional)
                         monthNamesShort  (string[12]) abbreviated names of the months (optional)
                         monthNames       (string[12]) names of the months (optional)
       @return  (string) the date in the above format */
    formatDate: function (format, date, settings) {
        if (!date)
            return '';
        var dayNamesShort = (settings ? settings.dayNamesShort : null) || this._defaults.dayNamesShort;
        var dayNames = (settings ? settings.dayNames : null) || this._defaults.dayNames;
        var monthNamesShort = (settings ? settings.monthNamesShort : null) || this._defaults.monthNamesShort;
        var monthNames = (settings ? settings.monthNames : null) || this._defaults.monthNames;
        // Check whether a format character is doubled
        var lookAhead = function(match) {
            var matches = (iFormat + 1 < format.length && format.charAt(iFormat + 1) == match);
            if (matches)
                iFormat++;
            return matches;
        };
        // Format a number, with leading zero if necessary
        var formatNumber = function(match, value, len) {
            var num = '' + value;
            if (lookAhead(match))
                while (num.length < len)
                    num = '0' + num;
            return num;
        };
        // Format a name, short or long as requested
        var formatName = function(match, value, indices, longNames) {
            return (lookAhead(match) ? longNames[value] : indices[value]);
        };
        var output = '';
        var literal = false;
        if (date)
            for (var iFormat = 0; iFormat < format.length; iFormat++) {
                if (literal)
                    if (format.charAt(iFormat) == "'" && !lookAhead("'"))
                        literal = false;
                    else
                        output += format.charAt(iFormat);
                else
                    switch (format.charAt(iFormat)) {
                        case 'd':
                            output += formatNumber('d', date.getDate(), 2);
                            break;
                        case 'D':
                            output += formatName('D', date.getDay(), dayNamesShort, dayNames);
                            break;
                        case 'o':
                            output += formatNumber('o',
                                (date.getTime() - new Date(date.getFullYear(), 0, 0).getTime()) / 86400000, 3);
                            break;
                        case 'm':
                            output += formatNumber('m', date.getMonth() + 1, 2);
                            break;
                        case 'M':
                            output += formatName('M', date.getMonth(), monthNamesShort, monthNames);
                            break;
                        case 'y':
                            output += (lookAhead('y') ? date.getFullYear() :
                                (date.getFullYear() % 100 < 10 ? '0' : '') + date.getFullYear() % 100);
                            break;
                        case '@':
                            output += date.getTime();
                            break;
                        case '!':
                            output += date.getTime() * 10000 + this._ticksTo1970;
                            break;
                        case "'":
                            if (lookAhead("'"))
                                output += "'";
                            else
                                literal = true;
                            break;
                        default:
                            output += format.charAt(iFormat);
                    }
            }
        return output;
    },

    /* Get a setting value, defaulting if necessary.
       @param  inst  (object) the instance settings for this datepicker
       @param  name  (string) the name of the property
       @return  (any) the property's value */
    _get: function(inst, name) {
        return inst.settings[name] !== undefined ?
            inst.settings[name] : this._defaults[name];
    },

    /* Parse existing date and initialise date picker.
       @param  inst  (object) the instance settings for this datepicker */
    _setDateFromField: function(inst) {
        var dateFormat = this._get(inst, 'dateFormat');
        var rangeSelect = this._get(inst, 'rangeSelect');
        var multiSelect = this._get(inst, 'multiSelect');
        var dates = (inst.input ? inst.input.val() : '');
        dates = (rangeSelect ? dates.split(this._get(inst, 'rangeSeparator')) :
            (multiSelect ? dates.split(this._get(inst, 'multiSeparator')) : [dates]));
        inst.dates = [];
        var settings = this._getFormatConfig(inst);
        for (var i = 0; i < dates.length; i++)
            try {
                inst.dates[i] = this.parseDate(dateFormat, dates[i], settings);
            }
            catch (event) {
                inst.dates[i] = null;
            }
        for (var i = inst.dates.length - 1; i >= 0; i--)
            if (!inst.dates[i])
                inst.dates.splice(i, 1);
        if (rangeSelect && inst.dates.length < 2)
            inst.dates[1] = inst.dates[0];
        if (multiSelect && inst.dates.length > multiSelect)
            inst.dates.splice(multiSelect, inst.dates.length);
        inst.cursorDate = new Date((inst.dates[0] || this._getDefaultDate(inst)).getTime());
        inst.drawMonth = inst.cursorDate.getMonth();
        inst.drawYear = inst.cursorDate.getFullYear();
        this._adjustInstDate(inst);
    },

    /* Retrieve the default date shown on opening.
       @param  inst  (object) the instance settings for this datepicker
       @return  (Date) the default date */
    _getDefaultDate: function(inst) {
        return this._restrictMinMax(inst,
            this._determineDate(this._get(inst, 'defaultDate'), new Date()));
    },

    /* A date may be specified as an exact value or a relative one.
       @param  date         (Date or number or string) the date or offset
       @param  defaultDate  (Date) the date to use if no other supplied
       @return  (Date) the decoded date */
    _determineDate: function(date, defaultDate) {
        var offsetNumeric = function(offset) {
            var date = new Date();
            date.setDate(date.getDate() + offset);
            return date;
        };
        var offsetString = function(offset) {
            var date = new Date();
            var year = date.getFullYear();
            var month = date.getMonth();
            var day = date.getDate();
            var pattern = /([+-]?[0-9]+)\s*(d|w|m|y)?/g;
            var matches = pattern.exec(offset.toLowerCase());
            while (matches) {
                switch (matches[2] || 'd') {
                    case 'd':
                        day += parseInt(matches[1], 10); break;
                    case 'w':
                        day += parseInt(matches[1], 10) * 7; break;
                    case 'm':
                        month += parseInt(matches[1], 10);
                        day = Math.min(day, $.datepick._getDaysInMonth(year, month));
                        break;
                    case 'y':
                        year += parseInt(matches[1], 10);
                        day = Math.min(day, $.datepick._getDaysInMonth(year, month));
                        break;
                }
                matches = pattern.exec(offset.toLowerCase());
            }
            return new Date(year, month, day);
        };
        date = (date == null ? defaultDate : (typeof date == 'string' ? offsetString(date) :
            (typeof date == 'number' ? (isNaN(date) || date == Infinity || date == -Infinity ?
            defaultDate : offsetNumeric(date)) : date)));
        date = (date && (date.toString() == 'Invalid Date' ||
            date.toString() == 'NaN') ? defaultDate : date);
        if (date) {
            date.setHours(0);
            date.setMinutes(0);
            date.setSeconds(0);
            date.setMilliseconds(0);
        }
        return this._daylightSavingAdjust(date);
    },

    /* Handle switch to/from daylight saving.
       Hours may be non-zero on daylight saving cut-over:
       > 12 when midnight changeover, but then cannot generate
       midnight datetime, so jump to 1AM, otherwise reset.
       @param  date  (Date) the date to check
       @return  (Date) the corrected date */
    _daylightSavingAdjust: function(date) {
        if (!date) return null;
        date.setHours(date.getHours() > 12 ? date.getHours() + 2 : 0);
        return date;
    },

    /* Set the date(s) directly.
       @param  inst     (object) the instance settings for this datepicker
       @param  date     (Date or Date[] or number or string) the new date or start of a range
       @param  endDate  (Date or number or string) the end of a range */
    _setDate: function(inst, date, endDate) {
        date = (!date ? [] : (isArray(date) ? date : [date]));
        if (endDate)
            date.push(endDate);
        var clear = (date.length == 0);
        var origMonth = inst.cursorDate.getMonth();
        var origYear = inst.cursorDate.getFullYear();
        inst.dates = [];
        inst.dates[0] = this._restrictMinMax(inst, this._determineDate(date[0], new Date()));
        inst.cursorDate = new Date(inst.dates[0].getTime());
        inst.drawMonth = inst.cursorDate.getMonth();
        inst.drawYear = inst.cursorDate.getFullYear();
        if (this._get(inst, 'rangeSelect'))
            inst.dates[1] = (date.length < 1 ? inst.dates[0] :
                this._restrictMinMax(inst, this._determineDate(date[1], null)));
        else if (this._get(inst, 'multiSelect'))
            for (var i = 1; i < date.length; i++)
                inst.dates[i] = this._restrictMinMax(inst, this._determineDate(date[i], null));
        if (origMonth != inst.cursorDate.getMonth() || origYear != inst.cursorDate.getFullYear())
            this._notifyChange(inst);
        this._adjustInstDate(inst);
        this._showDate(inst);
    },

    /* Retrieve the date(s) directly.
       @param  inst  (object) the instance settings for this datepicker
       @return  (Date or Date[2] or Date[]) the current date or dates
                (for a range or multiples) */
    _getDate: function(inst) {
        var startDate = (inst.input && inst.input.val() == '' ? null : inst.dates[0]);
        if (this._get(inst, 'rangeSelect'))
            return (startDate ? [inst.dates[0], inst.dates[1] || inst.dates[0]] : [null, null]);
        else if (this._get(inst, 'multiSelect'))
            return inst.dates.slice(0, inst.dates.length);
        else
            return startDate;
    },

    /* Generate the HTML for the current state of the date picker.
       @param  inst  (object) the instance settings for this datepicker
       @return  (string) the new HTML for the datepicker */
    _generateHTML: function(inst) {
        var today = new Date();
        today = this._daylightSavingAdjust(
            new Date(today.getFullYear(), today.getMonth(), today.getDate())); // Clear time
        var showStatus = this._get(inst, 'showStatus');
        var initStatus = this._get(inst, 'initStatus') || '&#xa0;';
        var isRTL = this._get(inst, 'isRTL');
        // Build the date picker HTML
        var clear = (this._get(inst, 'mandatory') ? '' :
            '<div class="datepick-clear"><a href="javascript:void(0)" onclick="jQuery.datepick._clearDate(\'#' + inst.id + '\');"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'clearStatus'), initStatus) + '>' +
            this._get(inst, 'clearText') + '</a></div>');
        var controls = '<div class="datepick-control">' + (isRTL ? '' : clear) +
            '<div class="datepick-close"><a href="javascript:void(0)" onclick="jQuery.datepick._hideDatepick();"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'closeStatus'), initStatus) + '>' +
            this._get(inst, 'closeText') + '</a></div>' + (isRTL ? clear : '')  + '</div>';
        var prompt = this._get(inst, 'prompt');
        var closeAtTop = this._get(inst, 'closeAtTop');
        var hideIfNoPrevNext = this._get(inst, 'hideIfNoPrevNext');
        var navigationAsDateFormat = this._get(inst, 'navigationAsDateFormat');
        var showBigPrevNext = this._get(inst, 'showBigPrevNext');
        var numMonths = this._getNumberOfMonths(inst);
        var showCurrentAtPos = this._get(inst, 'showCurrentAtPos');
        var stepMonths = this._get(inst, 'stepMonths');
        var stepBigMonths = this._get(inst, 'stepBigMonths');
        var isMultiMonth = (numMonths[0] != 1 || numMonths[1] != 1);
        var minDate = this._getMinMaxDate(inst, 'min', true);
        var maxDate = this._getMinMaxDate(inst, 'max');
        var drawMonth = inst.drawMonth - showCurrentAtPos;
        var drawYear = inst.drawYear;
        if (drawMonth < 0) {
            drawMonth += 12;
            drawYear--;
        }
        if (maxDate) { // Don't show past maximum unless also restricted by minimum
            var maxDraw = this._daylightSavingAdjust(new Date(maxDate.getFullYear(),
                maxDate.getMonth() - numMonths[1] + 1, maxDate.getDate()));
            maxDraw = (minDate && maxDraw < minDate ? minDate : maxDraw);
            while (this._daylightSavingAdjust(new Date(drawYear, drawMonth, 1)) > maxDraw) {
                drawMonth--;
                if (drawMonth < 0) {
                    drawMonth = 11;
                    drawYear--;
                }
            }
        }
        inst.drawMonth = drawMonth;
        inst.drawYear = drawYear;
        // Controls and links
        var prevText = this._get(inst, 'prevText');
        prevText = (!navigationAsDateFormat ? prevText : this.formatDate(prevText,
            this._daylightSavingAdjust(new Date(drawYear, drawMonth - stepMonths, 1)),
            this._getFormatConfig(inst)));
        var prevBigText = (showBigPrevNext ? this._get(inst, 'prevBigText') : '');
        prevBigText = (!navigationAsDateFormat ? prevBigText : this.formatDate(prevBigText,
            this._daylightSavingAdjust(new Date(drawYear, drawMonth - stepBigMonths, 1)),
            this._getFormatConfig(inst)));
        var prev = '<div class="datepick-prev">' + (this._canAdjustMonth(inst, -1, drawYear, drawMonth) ?
            (showBigPrevNext ? '<a href="javascript:void(0)" onclick="jQuery.datepick._adjustDate(\'#' + inst.id + '\', -' + stepBigMonths + ', \'M\');"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'prevBigStatus'), initStatus) + '>' + prevBigText + '</a>' : '') +
            '<a href="javascript:void(0)" onclick="jQuery.datepick._adjustDate(\'#' + inst.id + '\', -' + stepMonths + ', \'M\');"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'prevStatus'), initStatus) + '>' + prevText + '</a>' :
            (hideIfNoPrevNext ? '&#xa0;' : (showBigPrevNext ? '<label>' + prevBigText + '</label>' : '') +
            '<label>' + prevText + '</label>')) + '</div>';
        var nextText = this._get(inst, 'nextText');
        nextText = (!navigationAsDateFormat ? nextText : this.formatDate(nextText,
            this._daylightSavingAdjust(new Date(drawYear, drawMonth + stepMonths, 1)),
            this._getFormatConfig(inst)));
        var nextBigText = (showBigPrevNext ? this._get(inst, 'nextBigText') : '');
        nextBigText = (!navigationAsDateFormat ? nextBigText : this.formatDate(nextBigText,
            this._daylightSavingAdjust(new Date(drawYear, drawMonth + stepBigMonths, 1)),
            this._getFormatConfig(inst)));
        var next = '<div class="datepick-next">' + (this._canAdjustMonth(inst, +1, drawYear, drawMonth) ?
            '<a href="javascript:void(0)" onclick="jQuery.datepick._adjustDate(\'#' + inst.id + '\', +' + stepMonths + ', \'M\');"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'nextStatus'), initStatus) + '>' + nextText + '</a>' +
            (showBigPrevNext ? '<a href="javascript:void(0)" onclick="jQuery.datepick._adjustDate(\'#' + inst.id + '\', +' + stepBigMonths + ', \'M\');"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'nextBigStatus'), initStatus) + '>' + nextBigText + '</a>' : '') :
            (hideIfNoPrevNext ? '&#xa0;' : '<label>' + nextText + '</label>' +
            (showBigPrevNext ? '<label>' + nextBigText + '</label>' : ''))) + '</div>';
        var currentText = this._get(inst, 'currentText');
        var gotoDate = (this._get(inst, 'gotoCurrent') && inst.dates[0] ? inst.dates[0] : today);
        currentText = (!navigationAsDateFormat ? currentText :
            this.formatDate(currentText, gotoDate, this._getFormatConfig(inst)));
        var html = (closeAtTop && !inst.inline ? controls : '') +
            '<div class="datepick-links">' + (isRTL ? next : prev) +
            (this._isInRange(inst, gotoDate) ? '<div class="datepick-current">' +
            '<a href="javascript:void(0)" onclick="jQuery.datepick._gotoToday(\'#' + inst.id + '\');"' +
            this._addStatus(showStatus, inst.id, this._get(inst, 'currentStatus'), initStatus) + '>' +
            currentText + '</a></div>' : '') + (isRTL ? prev : next) + '</div>' +
            (prompt ? '<div class="' + this._promptClass + '"><span>' + prompt + '</span></div>' : '');
        var firstDay = parseInt(this._get(inst, 'firstDay'), 10);
        firstDay = (isNaN(firstDay) ? 0 : firstDay);
        var changeFirstDay = this._get(inst, 'changeFirstDay');
        var dayNames = this._get(inst, 'dayNames');
        var dayNamesShort = this._get(inst, 'dayNamesShort');
        var dayNamesMin = this._get(inst, 'dayNamesMin');
        var monthNames = this._get(inst, 'monthNames');
        var beforeShowDay = this._get(inst, 'beforeShowDay');
        var highlightWeek = this._get(inst, 'highlightWeek');
        var showOtherMonths = this._get(inst, 'showOtherMonths');
        var selectOtherMonths = this._get(inst, 'selectOtherMonths');
        var showWeeks = this._get(inst, 'showWeeks');
        var calculateWeek = this._get(inst, 'calculateWeek') || this.iso8601Week;
        var weekStatus = this._get(inst, 'weekStatus');
        var status = (showStatus ? this._get(inst, 'dayStatus') || initStatus : '');
        var dateStatus = this._get(inst, 'statusForDate') || this.dateStatus;
        var onHover = this._get(inst, 'onHover');
        var defaultDate = this._getDefaultDate(inst);
        for (var row = 0; row < numMonths[0]; row++)
            for (var col = 0; col < numMonths[1]; col++) {
                var cursorDate = this._daylightSavingAdjust(new Date(drawYear, drawMonth, inst.cursorDate.getDate()));
                html += '<div class="' + this._oneMonthClass + (col == 0 ? ' datepick-new-row' : '') + '">' +
                    this._generateMonthYearHeader(inst, drawMonth, drawYear, minDate, maxDate,
                    cursorDate, row > 0 || col > 0, showStatus, initStatus, monthNames) + // Draw month headers
                    '<table class="datepick" cellpadding="0" cellspacing="0"><thead>' +
                    '<tr class="datepick-title-row">' +
                    (showWeeks ? '<th' + this._addStatus(showStatus, inst.id, weekStatus, initStatus) + '>' +
                    this._get(inst, 'weekHeader') + '</th>' : '');
                for (var dow = 0; dow < 7; dow++) { // Days of the week
                    var day = (dow + firstDay) % 7;
                    var dayStatus = (!showStatus || !changeFirstDay ? '' :
                        status.replace(/DD/, dayNames[day]).replace(/D/, dayNamesShort[day]));
                    html += '<th' + ((dow + firstDay + 6) % 7 < 5 ? '' : ' class="datepick-week-end-cell"') + '>' +
                        (!changeFirstDay ? '<span' + this._addStatus(showStatus, inst.id, dayNames[day], initStatus) :
                        '<a href="javascript:void(0)" onclick="jQuery.datepick._changeFirstDay(\'#' + inst.id + '\', ' + day + ');"' +
                        this._addStatus(showStatus, inst.id, dayStatus, initStatus)) + ' title="' + dayNames[day] + '">' +
                        dayNamesMin[day] + (changeFirstDay ? '</a>' : '</span>') + '</th>';
                }
                html += '</tr></thead><tbody>';
                var daysInMonth = this._getDaysInMonth(drawYear, drawMonth);
                if (drawYear == inst.cursorDate.getFullYear() && drawMonth == inst.cursorDate.getMonth())
                    inst.cursorDate.setDate(Math.min(inst.cursorDate.getDate(), daysInMonth));
                var leadDays = (this._getFirstDayOfMonth(drawYear, drawMonth) - firstDay + 7) % 7;
                var numRows = (isMultiMonth ? 6 : Math.ceil((leadDays + daysInMonth) / 7)); // Calculate the number of rows to generate
                var printDate = this._daylightSavingAdjust(new Date(drawYear, drawMonth, 1 - leadDays));
                for (var dRow = 0; dRow < numRows; dRow++) { // Create date picker rows
                    html += '<tr class="datepick-days-row">' +
                        (showWeeks ? '<td class="datepick-week-col"' +
                        this._addStatus(showStatus, inst.id, weekStatus, initStatus) + '>' +
                        calculateWeek(printDate) + '</td>' : '');
                    for (var dow = 0; dow < 7; dow++) { // Create date picker days
                        var daySettings = (beforeShowDay ?
                            beforeShowDay.apply((inst.input ? inst.input[0] : null), [printDate]) : [true, '']);
                        var otherMonth = (printDate.getMonth() != drawMonth);
                        var unselectable = (otherMonth && !selectOtherMonths) || !daySettings[0] ||
                            (minDate && printDate < minDate) || (maxDate && printDate > maxDate);
                        var current = (this._get(inst, 'rangeSelect') && inst.dates[0] &&
                            printDate.getTime() >= inst.dates[0].getTime() &&
                            printDate.getTime() <= (inst.dates[1] || inst.dates[0]).getTime());
                        for (var i = 0; i < inst.dates.length; i++)
                            current = current || (inst.dates[i] &&
                                printDate.getTime() == inst.dates[i].getTime());
                        var empty = otherMonth && !showOtherMonths;
                        html += '<td class="datepick-days-cell' +
                            ((dow + firstDay + 6) % 7 >= 5 ? ' datepick-week-end-cell' : '') + // Highlight weekends
                            (otherMonth ? ' datepick-other-month' : '') + // Highlight days from other months
                            ((printDate.getTime() == cursorDate.getTime() &&
                            drawMonth == inst.cursorDate.getMonth() && inst._keyEvent) || // User pressed key
                            (defaultDate.getTime() == printDate.getTime() && defaultDate.getTime() == cursorDate.getTime()) ?
                            // Or defaultDate is current printedDate and defaultDate is cursorDate
                            ' ' + $.datepick._dayOverClass : '') + // Highlight selected day
                            (unselectable ? ' ' + this._unselectableClass : '') +  // Highlight unselectable days
                            (empty ? '' : ' ' + daySettings[1] + // Highlight custom dates
                            (current ? ' ' + this._currentClass : '') + // Currently selected
                            (printDate.getTime() == today.getTime() ? ' datepick-today' : '')) + '"' + // Highlight today (if different)
                            (!empty && daySettings[2] ? ' title="' + daySettings[2] + '"' : '') + // Cell title
                            ' onmouseover="' + (unselectable ? '' : 'jQuery(this).parents(\'tbody\').' +
                            'find(\'td\').removeClass(\'' + this._dayOverClass + '\').end().end().' +
                            'addClass(\'' + this._dayOverClass + '\');') + // Cursor
                            (highlightWeek ? 'jQuery(this).parent().parent().' +
                            'find(\'tr\').removeClass(\'' + this._weekOverClass + '\').end().end().' +
                            'addClass(\'' + this._weekOverClass + '\');' : '') + // Highlight week
                            (!showStatus || empty ? '' : 'jQuery(\'#datepick-status-' + inst.id + '\').html(\'' + // Show status
                            (dateStatus.apply((inst.input ? inst.input[0] : null), [printDate, inst]) || initStatus) +'\');') +
                            (onHover && !empty ? 'jQuery.datepick._doHover(\'#' + // onHover
                            inst.id + '\',' + printDate.getFullYear() + ',' + printDate.getMonth() + ', this);' : '') + '"' +
                            ' onmouseout="' + (unselectable ? '' :
                            'jQuery(this).removeClass(\'' + this._dayOverClass + '\');') + // Remove cursor
                            (!showStatus || empty ? '' : 'jQuery(\'#datepick-status-' +
                            inst.id + '\').' + 'html(\'' + initStatus + '\');') +
                            (onHover && !empty ? 'jQuery.datepick._doHover(\'#' + inst.id + '\');' : '') + '"' + // onHover
                            (unselectable ? '' : ' onclick="jQuery.datepick._selectDay(\'#' + // Select
                            inst.id + '\'' + ',' + printDate.getTime() + ',this);"') + '>' +
                            (empty ? '&#xa0;' : // Not showing other months
                            (unselectable ? printDate.getDate() : '<a>' + printDate.getDate() + '</a>')) + '</td>'; // Display for this month
                        printDate.setDate(printDate.getDate() + 1);
                        printDate = this._daylightSavingAdjust(printDate);
                    }
                    html += '</tr>';
                }
                drawMonth++;
                if (drawMonth > 11) {
                    drawMonth = 0;
                    drawYear++;
                }
                html += '</tbody></table></div>';
            }
        html += (showStatus ? '<div style="clear: both;"></div><div id="datepick-status-' + inst.id +
            '" class="datepick-status">' + initStatus + '</div>' : '') +
            (!closeAtTop && !inst.inline ? controls : '') +
            '<div style="clear: both;"></div>' +
            ($.browser.msie && parseInt($.browser.version, 10) < 7 && !inst.inline ?
            '<iframe src="javascript:false;" class="' + this._coverClass + '"></iframe>' : '');
        inst._keyEvent = false;
        return html;
    },

    /* Generate the month and year header.
       @param  inst  (object) the instance settings for this datepicker
       @param  drawMonth  (number) the current month
       @param  drawYear   (number) the current year
       @param  minDate    (Date) the minimum allowed date or null if none
       @param  maxDate    (Date) the maximum allowed date or null if none
       @return  (string) the HTML for the month and year */
    _generateMonthYearHeader: function(inst, drawMonth, drawYear, minDate, maxDate,
            cursorDate, secondary, showStatus, initStatus, monthNames) {
        var minDraw = this._daylightSavingAdjust(new Date(drawYear, drawMonth, 1));
        minDate = (minDate < minDraw ? minDate : minDraw);
        var changeMonth = this._get(inst, 'changeMonth');
        var changeYear = this._get(inst, 'changeYear');
        var showMonthAfterYear = this._get(inst, 'showMonthAfterYear');
        var html = '<div class="datepick-header">';
        var monthHtml = '';
        // Month selection
        if (secondary || !changeMonth)
            monthHtml += '<span>' + monthNames[drawMonth] + '</span>';
        else {
            var inMinYear = (minDate && minDate.getFullYear() == drawYear);
            var inMaxYear = (maxDate && maxDate.getFullYear() == drawYear);
            monthHtml += '<select class="datepick-new-month" ' +
                'onchange="jQuery.datepick._selectMonthYear(\'#' + inst.id + '\', this, \'M\');" ' +
                'onclick="jQuery.datepick._clickMonthYear(\'#' + inst.id + '\');"' +
                this._addStatus(showStatus, inst.id, this._get(inst, 'monthStatus'), initStatus) + '>';
            for (var month = 0; month < 12; month++) {
                if ((!inMinYear || month >= minDate.getMonth()) &&
                        (!inMaxYear || month <= maxDate.getMonth()))
                    monthHtml += '<option value="' + month + '"' +
                        (month == drawMonth ? ' selected="selected"' : '') +
                        '>' + monthNames[month] + '</option>';
            }
            monthHtml += '</select>';
        }
        if (!showMonthAfterYear)
            html += monthHtml + (secondary || !changeMonth || !changeYear ? '&#xa0;' : '');
        // Year selection
        if (secondary || !changeYear)
            html += '<span>' + drawYear + '</span>';
        else {
            // Determine range of years to display
            var years = this._get(inst, 'yearRange').split(':');
            var year = 0;
            var endYear = 0;
            if (years.length != 2) {
                year = drawYear - 10;
                endYear = drawYear + 10;
            } else if (years[0].charAt(0) == '+' || years[0].charAt(0) == '-') {
                year = drawYear + parseInt(years[0], 10);
                endYear = drawYear + parseInt(years[1], 10);
            } else {
                year = parseInt(years[0], 10);
                endYear = parseInt(years[1], 10);
            }
            year = (minDate ? Math.max(year, minDate.getFullYear()) : year);
            endYear = (maxDate ? Math.min(endYear, maxDate.getFullYear()) : endYear);
            html += '<select class="datepick-new-year" ' +
                'onchange="jQuery.datepick._selectMonthYear(\'#' + inst.id + '\', this, \'Y\');" ' +
                'onclick="jQuery.datepick._clickMonthYear(\'#' + inst.id + '\');"' +
                this._addStatus(showStatus, inst.id, this._get(inst, 'yearStatus'), initStatus) + '>';
            for (; year <= endYear; year++) {
                html += '<option value="' + year + '"' +
                    (year == drawYear ? ' selected="selected"' : '') +
                    '>' + year + '</option>';
            }
            html += '</select>';
        }
        html += this._get(inst, 'yearSuffix');
        if (showMonthAfterYear)
            html += (secondary || !changeMonth || !changeYear ? '&#xa0;' : '') + monthHtml;
        html += '</div>'; // Close datepicker_header
        return html;
    },

    /* Provide code to set and clear the status panel.
       @param  showStatus  (boolean) true if the status bar is shown
       @param  id          (string) the ID of the datepicker instance
       @param  text        (string) the status text to display
       @param  initStatus  (string) the default status message
       @return  (string) hover actions for the status messages */
    _addStatus: function(showStatus, id, text, initStatus) {
        return (showStatus ? ' onmouseover="jQuery(\'#datepick-status-' + id +
            '\').html(\'' + (text || initStatus) + '\');" ' +
            'onmouseout="jQuery(\'#datepick-status-' + id +
            '\').html(\'' + initStatus + '\');"' : '');
    },

    /* Adjust one of the date sub-fields.
       @param  inst    (object) the instance settings for this datepicker
       @param  offset  (number) the change to apply
       @param  period  (string) 'D' for days, 'M' for months, 'Y' for years */
    _adjustInstDate: function(inst, offset, period) {
        var year = inst.drawYear + (period == 'Y' ? offset : 0);
        var month = inst.drawMonth + (period == 'M' ? offset : 0);
        var day = Math.min(inst.cursorDate.getDate(), this._getDaysInMonth(year, month)) +
            (period == 'D' ? offset : 0);
        inst.cursorDate = this._restrictMinMax(inst,
            this._daylightSavingAdjust(new Date(year, month, day)));
        inst.drawMonth = inst.cursorDate.getMonth();
        inst.drawYear = inst.cursorDate.getFullYear();
        if (period == 'M' || period == 'Y')
            this._notifyChange(inst);
    },

    /* Ensure a date is within any min/max bounds.
       @param  inst  (object) the instance settings for this datepicker
       @param  date  (Date) the date to check
       @return  (Date) the restricted date */
    _restrictMinMax: function(inst, date) {
        var minDate = this._getMinMaxDate(inst, 'min', true);
        var maxDate = this._getMinMaxDate(inst, 'max');
        date = (minDate && date < minDate ? minDate : date);
        date = (maxDate && date > maxDate ? maxDate : date);
        return date;
    },

    /* Notify change of month/year.
       @param  inst  (object) the instance settings for this datepicker */
    _notifyChange: function(inst) {
        var onChange = this._get(inst, 'onChangeMonthYear');
        if (onChange)
            onChange.apply((inst.input ? inst.input[0] : null),
                [inst.cursorDate.getFullYear(), inst.cursorDate.getMonth() + 1,
                this._daylightSavingAdjust(new Date(
                inst.cursorDate.getFullYear(), inst.cursorDate.getMonth(), 1)), inst]);
    },

    /* Determine the number of months to show.
       @param  inst  (object) the instance settings for this datepicker
       @return  (number[2]) the number of rows and columns to display */
    _getNumberOfMonths: function(inst) {
        var numMonths = this._get(inst, 'numberOfMonths');
        return (numMonths == null ? [1, 1] :
            (typeof numMonths == 'number' ? [1, numMonths] : numMonths));
    },

    /* Determine the current minimum/maximum date.
       Ensure no time components are set. May be overridden for a range.
       @param  inst        (object) the instance settings for this datepicker
       @param  minMax      (string) 'min' or 'max' for required date
       @param  checkRange  (boolean) true to allow override for a range minimum
       @return  (Date) the minimum/maximum date or null if none */
    _getMinMaxDate: function(inst, minMax, checkRange) {
        var date = this._determineDate(this._get(inst, minMax + 'Date'), null);
        var rangeMin = this._getRangeMin(inst);
        return (checkRange && rangeMin && (!date || rangeMin > date) ? rangeMin : date);
    },

    /* Retrieve the temporary range minimum when in the process of selecting.
       @param  inst  (object) the instance settings for this datepicker
       @return  (Date) the temporary minimum or null */
    _getRangeMin: function(inst) {
        return (this._get(inst, 'rangeSelect') && inst.dates[0] &&
            !inst.dates[1] ? inst.dates[0] : null);
    },

    /* Find the number of days in a given month.
       @param  year   (number) the full year
       @param  month  (number) the month (0 to 11)
       @return  (number) the number of days in this month */
    _getDaysInMonth: function(year, month) {
        return 32 - new Date(year, month, 32).getDate();
    },

    /* Find the day of the week of the first of a month.
       @param  year   (number) the full year
       @param  month  (number) the month (0 to 11)
       @return  (number) 0 = Sunday, 1 = Monday, ... */
    _getFirstDayOfMonth: function(year, month) {
        return new Date(year, month, 1).getDay();
    },

    /* Determines if we should allow a "prev/next" month display change.
       @param  inst      (object) the instance settings for this datepicker
       @param  offset    (number) the number of months to change by
       @param  curYear   (number) the full current year
       @param  curMonth  (number) the current month (0 to 11)
       @return  (boolean) true if prev/next allowed, false if not */
    _canAdjustMonth: function(inst, offset, curYear, curMonth) {
        var numMonths = this._getNumberOfMonths(inst);
        var date = this._daylightSavingAdjust(new Date(
            curYear, curMonth + (offset < 0 ? offset : numMonths[1]), 1));
        if (offset < 0)
            date.setDate(this._getDaysInMonth(date.getFullYear(), date.getMonth()));
        return this._isInRange(inst, date);
    },

    /* Is the given date in the accepted range?
       @param  inst  (object) the instance settings for this datepicker
       @param  date  (Date) the date to check
       @return  (boolean) true if the date is in the allowed minimum/maximum, false if not */
    _isInRange: function(inst, date) {
        // During range selection, use minimum of selected date and range start
        var minDate = this._getRangeMin(inst) || this._getMinMaxDate(inst, 'min');
        var maxDate = this._getMinMaxDate(inst, 'max');
        return ((!minDate || date >= minDate) && (!maxDate || date <= maxDate));
    },

    /* Provide the configuration settings for formatting/parsing.
       @param  inst  (object) the instance settings for this datepicker
       @return  (object) the settings subset */
    _getFormatConfig: function(inst) {
        return {shortYearCutoff: this._get(inst, 'shortYearCutoff'),
            dayNamesShort: this._get(inst, 'dayNamesShort'), dayNames: this._get(inst, 'dayNames'),
            monthNamesShort: this._get(inst, 'monthNamesShort'), monthNames: this._get(inst, 'monthNames')};
    },

    /* Format the given date for display.
       @param  inst   (object) the instance settings for this datepicker
       @param  year   (number, optional) the full year
       @param  month  (number, optional) the month of the year (0 to 11)
       @param  day    (number, optional) the day of the month
       @return  (string) formatted date */
    _formatDate: function(inst, year, month, day) {
        if (!year)
            inst.dates[0] = new Date(inst.cursorDate.getTime());
        var date = (year ? (typeof year == 'object' ? year :
            this._daylightSavingAdjust(new Date(year, month, day))) : inst.dates[0]);
        return this.formatDate(this._get(inst, 'dateFormat'), date, this._getFormatConfig(inst));
    }
});

/* jQuery extend now ignores nulls!
   @param  target  (object) the object to extend
   @param  props   (object) the new settings
   @return  (object) the updated object */
function extendRemove(target, props) {
    $.extend(target, props);
    for (var name in props)
        if (props[name] == null || props[name] == undefined)
            target[name] = props[name];
    return target;
};

/* Determine whether an object is an array.
   @param  a  (object) the object to test
   @return  (boolean) true if an array, false if not */
function isArray(a) {
    return (a && a.constructor == Array);
};

/* Invoke the datepicker functionality.
   @param  options  (string) a command, optionally followed by additional parameters or
                    (object) settings for attaching new datepicker functionality
   @return  (jQuery) jQuery object */
$.fn.datepick = function(options){
    var otherArgs = Array.prototype.slice.call(arguments, 1);
    if (typeof options == 'string' && (options == 'isDisabled' ||
            options == 'getDate' || options == 'settings'))
        return $.datepick['_' + options + 'Datepick'].
            apply($.datepick, [this[0]].concat(otherArgs));
    if (options == 'option' && arguments.length == 2 && typeof arguments[1] == 'string')
        return $.datepick['_' + options + 'Datepick'].
            apply($.datepick, [this[0]].concat(otherArgs));
    return this.each(function() {
        typeof options == 'string' ?
            $.datepick['_' + options + 'Datepick'].
                apply($.datepick, [this].concat(otherArgs)) :
            $.datepick._attachDatepick(this, options);
    });
};

$.datepick = new Datepick(); // Singleton instance

$(function() {
    $(document).mousedown($.datepick._checkExternalClick).
        find('body').append($.datepick.dpDiv);
});

})(jQuery);

;
var IE6 = (navigator.userAgent.indexOf("MSIE 6")>=0) ? true : false;
if(IE6){
	$(function(){
		$("<div>")
			.css({
				'position': 'absolute',
				'top': '0px',
				'left': '0px',
				backgroundColor: 'black',
				'opacity': '0.75',
				'width': '100%',
				'height': $(window).height(),
				zIndex: 5000
			})
			.appendTo("body");
			
		$("<div><img src='/images/no-ie6.png' alt='' style='float: left;'/><p><br /><strong>Sorry! This page doesn't support Internet Explorer 6.</strong><br /><br />If you'd like to read our content please <a href='http://getfirefox.org'>upgrade your browser</a>.</p>")
			.css({
				backgroundColor: 'white',
				'top': '50%',
				'left': '50%',
				marginLeft: -210,
				marginTop: -100,
				width: 410,
				paddingRight: 10,
				height: 200,
				'position': 'absolute',
				zIndex: 6000
			})
			.appendTo("body");
	});		
}

;
// ColorBox v1.3.19 - jQuery lightbox plugin
// (c) 2011 Jack Moore - jacklmoore.com
// License: http://www.opensource.org/licenses/mit-license.php
(function(a,b,c){function Z(c,d,e){var g=b.createElement(c);return d&&(g.id=f+d),e&&(g.style.cssText=e),a(g)}function $(a){var b=y.length,c=(Q+a)%b;return c<0?b+c:c}function _(a,b){return Math.round((/%/.test(a)?(b==="x"?z.width():z.height())/100:1)*parseInt(a,10))}function ba(a){return K.photo||/\.(gif|png|jpe?g|bmp|ico)((#|\?).*)?$/i.test(a)}function bb(){var b;K=a.extend({},a.data(P,e));for(b in K)a.isFunction(K[b])&&b.slice(0,2)!=="on"&&(K[b]=K[b].call(P));K.rel=K.rel||P.rel||"nofollow",K.href=K.href||a(P).attr("href"),K.title=K.title||P.title,typeof K.href=="string"&&(K.href=a.trim(K.href))}function bc(b,c){a.event.trigger(b),c&&c.call(P)}function bd(){var a,b=f+"Slideshow_",c="click."+f,d,e,g;K.slideshow&&y[1]?(d=function(){F.text(K.slideshowStop).unbind(c).bind(j,function(){if(K.loop||y[Q+1])a=setTimeout(W.next,K.slideshowSpeed)}).bind(i,function(){clearTimeout(a)}).one(c+" "+k,e),r.removeClass(b+"off").addClass(b+"on"),a=setTimeout(W.next,K.slideshowSpeed)},e=function(){clearTimeout(a),F.text(K.slideshowStart).unbind([j,i,k,c].join(" ")).one(c,function(){W.next(),d()}),r.removeClass(b+"on").addClass(b+"off")},K.slideshowAuto?d():e()):r.removeClass(b+"off "+b+"on")}function be(b){U||(P=b,bb(),y=a(P),Q=0,K.rel!=="nofollow"&&(y=a("."+g).filter(function(){var b=a.data(this,e).rel||this.rel;return b===K.rel}),Q=y.index(P),Q===-1&&(y=y.add(P),Q=y.length-1)),S||(S=T=!0,r.show(),K.returnFocus&&a(P).blur().one(l,function(){a(this).focus()}),q.css({opacity:+K.opacity,cursor:K.overlayClose?"pointer":"auto"}).show(),K.w=_(K.initialWidth,"x"),K.h=_(K.initialHeight,"y"),W.position(),o&&z.bind("resize."+p+" scroll."+p,function(){q.css({width:z.width(),height:z.height(),top:z.scrollTop(),left:z.scrollLeft()})}).trigger("resize."+p),bc(h,K.onOpen),J.add(D).hide(),I.html(K.close).show()),W.load(!0))}function bf(){!r&&b.body&&(Y=!1,z=a(c),r=Z(X).attr({id:e,"class":n?f+(o?"IE6":"IE"):""}).hide(),q=Z(X,"Overlay",o?"position:absolute":"").hide(),s=Z(X,"Wrapper"),t=Z(X,"Content").append(A=Z(X,"LoadedContent","width:0; height:0; overflow:hidden"),C=Z(X,"LoadingOverlay").add(Z(X,"LoadingGraphic")),D=Z(X,"Title"),E=Z(X,"Current"),G=Z(X,"Next"),H=Z(X,"Previous"),F=Z(X,"Slideshow").bind(h,bd),I=Z(X,"Close")),s.append(Z(X).append(Z(X,"TopLeft"),u=Z(X,"TopCenter"),Z(X,"TopRight")),Z(X,!1,"clear:left").append(v=Z(X,"MiddleLeft"),t,w=Z(X,"MiddleRight")),Z(X,!1,"clear:left").append(Z(X,"BottomLeft"),x=Z(X,"BottomCenter"),Z(X,"BottomRight"))).find("div div").css({"float":"left"}),B=Z(X,!1,"position:absolute; width:9999px; visibility:hidden; display:none"),J=G.add(H).add(E).add(F),a(b.body).append(q,r.append(s,B)))}function bg(){return r?(Y||(Y=!0,L=u.height()+x.height()+t.outerHeight(!0)-t.height(),M=v.width()+w.width()+t.outerWidth(!0)-t.width(),N=A.outerHeight(!0),O=A.outerWidth(!0),r.css({"padding-bottom":L,"padding-right":M}),G.click(function(){W.next()}),H.click(function(){W.prev()}),I.click(function(){W.close()}),q.click(function(){K.overlayClose&&W.close()}),a(b).bind("keydown."+f,function(a){var b=a.keyCode;S&&K.escKey&&b===27&&(a.preventDefault(),W.close()),S&&K.arrowKey&&y[1]&&(b===37?(a.preventDefault(),H.click()):b===39&&(a.preventDefault(),G.click()))}),a("."+g,b).live("click",function(a){a.which>1||a.shiftKey||a.altKey||a.metaKey||(a.preventDefault(),be(this))})),!0):!1}var d={transition:"elastic",speed:300,width:!1,initialWidth:"600",innerWidth:!1,maxWidth:!1,height:!1,initialHeight:"450",innerHeight:!1,maxHeight:!1,scalePhotos:!0,scrolling:!0,inline:!1,html:!1,iframe:!1,fastIframe:!0,photo:!1,href:!1,title:!1,rel:!1,opacity:.9,preloading:!0,current:"image {current} of {total}",previous:"previous",next:"next",close:"close",open:!1,returnFocus:!0,reposition:!0,loop:!0,slideshow:!1,slideshowAuto:!0,slideshowSpeed:2500,slideshowStart:"start slideshow",slideshowStop:"stop slideshow",onOpen:!1,onLoad:!1,onComplete:!1,onCleanup:!1,onClosed:!1,overlayClose:!0,escKey:!0,arrowKey:!0,top:!1,bottom:!1,left:!1,right:!1,fixed:!1,data:undefined},e="colorbox",f="cbox",g=f+"Element",h=f+"_open",i=f+"_load",j=f+"_complete",k=f+"_cleanup",l=f+"_closed",m=f+"_purge",n=!a.support.opacity&&!a.support.style,o=n&&!c.XMLHttpRequest,p=f+"_IE6",q,r,s,t,u,v,w,x,y,z,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X="div",Y;if(a.colorbox)return;a(bf),W=a.fn[e]=a[e]=function(b,c){var f=this;b=b||{},bf();if(bg()){if(!f[0]){if(f.selector)return f;f=a("<a/>"),b.open=!0}c&&(b.onComplete=c),f.each(function(){a.data(this,e,a.extend({},a.data(this,e)||d,b))}).addClass(g),(a.isFunction(b.open)&&b.open.call(f)||b.open)&&be(f[0])}return f},W.position=function(a,b){function i(a){u[0].style.width=x[0].style.width=t[0].style.width=a.style.width,t[0].style.height=v[0].style.height=w[0].style.height=a.style.height}var c=0,d=0,e=r.offset(),g=z.scrollTop(),h=z.scrollLeft();z.unbind("resize."+f),r.css({top:-9e4,left:-9e4}),K.fixed&&!o?(e.top-=g,e.left-=h,r.css({position:"fixed"})):(c=g,d=h,r.css({position:"absolute"})),K.right!==!1?d+=Math.max(z.width()-K.w-O-M-_(K.right,"x"),0):K.left!==!1?d+=_(K.left,"x"):d+=Math.round(Math.max(z.width()-K.w-O-M,0)/2),K.bottom!==!1?c+=Math.max(z.height()-K.h-N-L-_(K.bottom,"y"),0):K.top!==!1?c+=_(K.top,"y"):c+=Math.round(Math.max(z.height()-K.h-N-L,0)/2),r.css({top:e.top,left:e.left}),a=r.width()===K.w+O&&r.height()===K.h+N?0:a||0,s[0].style.width=s[0].style.height="9999px",r.dequeue().animate({width:K.w+O,height:K.h+N,top:c,left:d},{duration:a,complete:function(){i(this),T=!1,s[0].style.width=K.w+O+M+"px",s[0].style.height=K.h+N+L+"px",K.reposition&&setTimeout(function(){z.bind("resize."+f,W.position)},1),b&&b()},step:function(){i(this)}})},W.resize=function(a){S&&(a=a||{},a.width&&(K.w=_(a.width,"x")-O-M),a.innerWidth&&(K.w=_(a.innerWidth,"x")),A.css({width:K.w}),a.height&&(K.h=_(a.height,"y")-N-L),a.innerHeight&&(K.h=_(a.innerHeight,"y")),!a.innerHeight&&!a.height&&(A.css({height:"auto"}),K.h=A.height()),A.css({height:K.h}),W.position(K.transition==="none"?0:K.speed))},W.prep=function(b){function g(){return K.w=K.w||A.width(),K.w=K.mw&&K.mw<K.w?K.mw:K.w,K.w}function h(){return K.h=K.h||A.height(),K.h=K.mh&&K.mh<K.h?K.mh:K.h,K.h}if(!S)return;var c,d=K.transition==="none"?0:K.speed;A.remove(),A=Z(X,"LoadedContent").append(b),A.hide().appendTo(B.show()).css({width:g(),overflow:K.scrolling?"auto":"hidden"}).css({height:h()}).prependTo(t),B.hide(),a(R).css({"float":"none"}),o&&a("select").not(r.find("select")).filter(function(){return this.style.visibility!=="hidden"}).css({visibility:"hidden"}).one(k,function(){this.style.visibility="inherit"}),c=function(){function q(){n&&r[0].style.removeAttribute("filter")}var b,c,g=y.length,h,i="frameBorder",k="allowTransparency",l,o,p;if(!S)return;l=function(){clearTimeout(V),C.hide(),bc(j,K.onComplete)},n&&R&&A.fadeIn(100),D.html(K.title).add(A).show();if(g>1){typeof K.current=="string"&&E.html(K.current.replace("{current}",Q+1).replace("{total}",g)).show(),G[K.loop||Q<g-1?"show":"hide"]().html(K.next),H[K.loop||Q?"show":"hide"]().html(K.previous),K.slideshow&&F.show();if(K.preloading){b=[$(-1),$(1)];while(c=y[b.pop()])o=a.data(c,e).href||c.href,a.isFunction(o)&&(o=o.call(c)),ba(o)&&(p=new Image,p.src=o)}}else J.hide();K.iframe?(h=Z("iframe")[0],i in h&&(h[i]=0),k in h&&(h[k]="true"),h.name=f+ +(new Date),K.fastIframe?l():a(h).one("load",l),h.src=K.href,K.scrolling||(h.scrolling="no"),a(h).addClass(f+"Iframe").appendTo(A).one(m,function(){h.src="//about:blank"})):l(),K.transition==="fade"?r.fadeTo(d,1,q):q()},K.transition==="fade"?r.fadeTo(d,0,function(){W.position(0,c)}):W.position(d,c)},W.load=function(b){var c,d,e=W.prep;T=!0,R=!1,P=y[Q],b||bb(),bc(m),bc(i,K.onLoad),K.h=K.height?_(K.height,"y")-N-L:K.innerHeight&&_(K.innerHeight,"y"),K.w=K.width?_(K.width,"x")-O-M:K.innerWidth&&_(K.innerWidth,"x"),K.mw=K.w,K.mh=K.h,K.maxWidth&&(K.mw=_(K.maxWidth,"x")-O-M,K.mw=K.w&&K.w<K.mw?K.w:K.mw),K.maxHeight&&(K.mh=_(K.maxHeight,"y")-N-L,K.mh=K.h&&K.h<K.mh?K.h:K.mh),c=K.href,V=setTimeout(function(){C.show()},100),K.inline?(Z(X).hide().insertBefore(a(c)[0]).one(m,function(){a(this).replaceWith(A.children())}),e(a(c))):K.iframe?e(" "):K.html?e(K.html):ba(c)?(a(R=new Image).addClass(f+"Photo").error(function(){K.title=!1,e(Z(X,"Error").text("This image could not be loaded"))}).load(function(){var a;R.onload=null,K.scalePhotos&&(d=function(){R.height-=R.height*a,R.width-=R.width*a},K.mw&&R.width>K.mw&&(a=(R.width-K.mw)/R.width,d()),K.mh&&R.height>K.mh&&(a=(R.height-K.mh)/R.height,d())),K.h&&(R.style.marginTop=Math.max(K.h-R.height,0)/2+"px"),y[1]&&(K.loop||y[Q+1])&&(R.style.cursor="pointer",R.onclick=function(){W.next()}),n&&(R.style.msInterpolationMode="bicubic"),setTimeout(function(){e(R)},1)}),setTimeout(function(){R.src=c},1)):c&&B.load(c,K.data,function(b,c,d){e(c==="error"?Z(X,"Error").text("Request unsuccessful: "+d.statusText):a(this).contents())})},W.next=function(){!T&&y[1]&&(K.loop||y[Q+1])&&(Q=$(1),W.load())},W.prev=function(){!T&&y[1]&&(K.loop||Q)&&(Q=$(-1),W.load())},W.close=function(){S&&!U&&(U=!0,S=!1,bc(k,K.onCleanup),z.unbind("."+f+" ."+p),q.fadeTo(200,0),r.stop().fadeTo(300,0,function(){r.add(q).css({opacity:1,cursor:"auto"}).hide(),bc(m),A.remove(),setTimeout(function(){U=!1,bc(l,K.onClosed)},1)}))},W.remove=function(){a([]).add(r).add(q).remove(),r=null,a("."+g).removeData(e).removeClass(g).die()},W.element=function(){return a(P)},W.settings=d})(jQuery,document,this);
;
$.fn.hasAttr = function (name) {
    var attr = $(this).attr(name);
    return typeof attr != undefined && attr !== false;
};

function Codeforces() {
    this.ping = function (pingUrl) {
        Codeforces.setCookie("lastOnlineTimeUpdaterInvocation", new Date().getTime());
        $.post(pingUrl, {}, function (result) {
            for (var i = 0; i < result.length; i++) {
                alert(result[i].name + "\n----------\n\n" + result[i].text);
            }
        }, "json");
    };

    this.parseSeconds = function (seconds) {
        var ap = 0;
        if (seconds.length == 9) {
            ap = seconds.charAt(0) - '0';
            seconds = seconds.substring(1);
        }
        if (seconds.length == 8 && seconds.charAt(2) == ':' && seconds.charAt(5) == ':') {
            var s = (seconds.charAt(7) - '0') + 10 * (seconds.charAt(6) - '0');
            var m = (seconds.charAt(4) - '0') + 10 * (seconds.charAt(3) - '0');
            var h = (seconds.charAt(1) - '0') + 10 * (seconds.charAt(0) - '0') + 100 * ap;
            return s + 60 * m + 60 * 60 * h;
        } else {
            return 0;
        }
    };

    this.formatSS = function (seconds) {
        if (seconds <= 9) {
            return "0" + seconds;
        } else {
            return seconds;
        }
    };

    this.formatSeconds = function (seconds) {
        var s = seconds % 60;
        seconds = (seconds - s) / 60;
        var m = seconds % 60;
        var h = (seconds - m) / 60;
        return Codeforces.formatSS(h) + ":" + Codeforces.formatSS(m) + ":" + Codeforces.formatSS(s);
    };

    this.countdown = function () {
        var now = new Date().getTime();
        var e = $(".countdown");
        var starts = new Array();

        var index = 0;
        e.each(function () {
            index++;
            $(this).attr("cdid", "i" + index);
        });

        var callback = function () {
            e.each(function () {
                var textBeforeRedirect = $(this).attr("textBeforeRedirect");
                var redirectUrl = $(this).attr("redirectUrl");
                var home = $(this).attr("home");
                var noRedirection = $(this).attr("noRedirection");

                var id = $(this).attr("cdid");
                var txt = $(this).text();
                var s = Codeforces.parseSeconds(txt);
                if (s > 0) {
                    if (starts[id] == undefined)
                        starts[id] = s;
                    var passed = Math.floor((new Date().getTime() - now) / 1000);
                    var val = starts[id] - passed;
                    if (val >= 0) {
                        $(this).text(Codeforces.formatSeconds(val));
                    }
                    if (val <= 0) {
                        if (noRedirection != "true" && noRedirection != "yes") {
                            if (textBeforeRedirect) {
                                Codeforces.alert(textBeforeRedirect, function () {
                                    if (redirectUrl) {
                                        window.setTimeout(Codeforces.redirect(redirectUrl), Math.floor(Math.random() * 2000));
                                    } else {
                                        window.setTimeout(Codeforces.reload, Math.floor(Math.random() * 2000));
                                    }
                                });
                            } else {
                                if (redirectUrl) {
                                    window.setTimeout(Codeforces.redirect(redirectUrl), Math.floor(Math.random() * 5000));
                                } else {
                                    window.setTimeout(Codeforces.reload, Math.floor(Math.random() * 5000));
                                }
                            }
                        } else {
                            if (textBeforeRedirect) {
                                Codeforces.alert(textBeforeRedirect);
                            }
                        }
                    }
                }
            });
            window.setTimeout(callback, 1000);
        };
        window.setTimeout(callback, 0);
    };

    this.facebox = function (target, home) {
        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        $.facebox.reveal($(target).clone().show(), null);
    };

    this.alert = function (messageHtml, okHandler, okText) {
        Codeforces.confirm(messageHtml, okHandler, null, okText, null);
    };

    this.confirm = function (messageHtml, okHandler, cancelHandler, okText, cancelText) {
        var dialogHtml = "<div class='confirm-proto'><div class='text'>&nbsp;<\/div><div><hr\/><div style='text-align:center;'><input class='ok' name='codeforces-dialog-ok-button' type='button' value='%OK%'\/><input class='cancel' name='codeforces-dialog-cancel-button' type='button' value='%Cancel%'\/><\/div><\/div><\/div>"
            .replace("%OK%", okText ? okText : "OK")
            .replace("%Cancel%", cancelText ? cancelText : "Cancel");
        var p = $(dialogHtml).css('display', 'none');
        $(".text", p).html(messageHtml);

        var defaultButtonName = null;

        var cancelButton = $(".cancel", p);
        if (cancelHandler) {
            cancelButton.click(function () {
                $.facebox.close();
                cancelHandler();
            });

            defaultButtonName = cancelButton.attr("name");
        } else {
            cancelButton.css("display", "none");
        }

        var okButton = $(".ok", p);
        if (okHandler) {
            okButton.click(function () {
                $.facebox.close();
                okHandler();
            });

            defaultButtonName = okButton.attr("name");
        } else {
            okButton.css("display", "none");
        }

        if (!okHandler && !cancelHandler) {
            $(".ok", p).parent().parent().css("display", "none");
        }

        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        $.facebox.reveal(p.show(), null);

        if (defaultButtonName) {
            $("input[name=" + defaultButtonName + "]").focus();
        }
    };

    this.showMessage = function (message) {
        $.jGrowl(message, {position:'bottom-right', life:10000});
    };

    this.focusOnError = function () {
        var found = false;

        $(".table-form .error").each(function () {
            if (!found) {
                var err = $(this);
                var val = $.trim(err.text());
                if (val.length > 0) {
                    var classes = err.attr("class").split(" ");
                    for (var i in classes) {
                        if (classes[i].match(/for__.*/)) {
                            var name = classes[i].substring(5);
                            found = true;

                            $(".table-form input[name=" + name + "]").focus();
                            return;
                        }
                    }
                }
            }
        });

        if (!found) {
            var focusInput = null;
            $("input.focus, select.focus, textarea.focus").each(function () {
                if (focusInput === null) {
                    focusInput = $(this);
                }
            });
            $(".table-form input, .table-form select, .table-form textarea").each(function () {
                if (focusInput === null) {
                    var elem = $(this);
                    if (elem.val() === "" && elem.attr("type") != "hidden" && !elem.hasAttr("readonly")) {
                        focusInput = elem;
                    }
                }
            });
            if (focusInput !== null) {
                focusInput.focus();
            }
        }
    };

    this.reload = function () {
        window.location.reload();
    };

    this.redirect = function (link) {
        window.location = link;
    };

    this.clearAjaxFormErrors = function (selector) {
        var form = $(selector);
        form.find("*").each(function () {
            var classes = $(this).attr("class").split(" ");
            var found = false;
            for (var i in classes) {
                if (classes[i].indexOf("error__") === 0) {
                    found = true;
                }
            }
            if (found) {
                $(this).find(".error").hide();
                $(this).find(".notice").show();
            }
        });
    };

    this.setAjaxFormError = function (selector, key, value) {
        $(selector).find("." + key).each(function () {
            $(".notice", this).hide();
            $(".error", this).html(value).show();
        });
    };

    this.setAjaxFormErrors = function (selector, data) {
        var result = false;
        this.clearAjaxFormErrors(selector);
        for (var i in data) {
            if (i.indexOf("error__") == 0) {
                this.setAjaxFormError(selector, i, data[i]);
                result = true;
            }
        }
        return result;
    };

    this.isEnglishText = function (s) {
        var latinLetterCount = 0;
        for (var i = 0; i < s.length; i++) {
            var c = s.charAt(i);
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                latinLetterCount++;
            }
        }
        return latinLetterCount > s.length / 2;
    };

    this.replaceDataForRoundTable = function (selector, titles, data, widths) {
        var rt = $(selector);
        var table = $(".rtable", rt);
        table.fadeOut(250, function () {
            var content = "";

            content += "<tr>";
            for (var j = 0; j < titles.length; j++) {
                var attr = "";
                if (j === 0) {
                    attr += " class=\"left\"";
                }
                if (widths != undefined && widths[j] != undefined) {
                    attr += " style=\"width:" + widths[j] + ";\"";
                }
                content += "<th" + attr + ">";
                content += titles[j] + "</th>";
            }
            content += "</tr>";

            for (var i = 0; i < data.length; i++) {
                var row = data[i];
                content += "<tr>";
                for (var j = 0; j < row.length; j++) {
                    var clazz = "";
                    if (j === 0) {
                        clazz += "left ";
                    }
                    if (i + 1 == data.length) {
                        clazz += "bottom ";
                    }
                    if (i % 2 === 0) {
                        clazz += "dark ";
                    }
                    content += "<td class=\"" + clazz + "\">" + row[j] + "</td>";
                }
                content += "</tr>";
            }
            table.html(content);
            table.fadeIn(250);
        });
    };

    /*
     this.changeRowIndex = function(selector, from, to) {
     if (from != to) {
     var init = $(selector + " tr:nth-child(" + from + ")");
     var target = $(selector + " tr:nth-child(" + to + ")");
     var duration = 250 + 50 * Math.abs(from - to);
     if (init != undefined && target != undefined) {
     var tr = init.clone();
     $(selector).append(tr);
     tr.css("display", "block").css("position", "absolute")
     .css("top", init.position().top).css("background", "#FFF7DB !important")
     .css("border", "3px solid #e1e1e1").css("font-size", "1.25em")
     .css("left", (target.position().left-10) + "px");
     tr.find("td").css("background", "#FFF7DB !important");
     tr.show();
     init.animate({
     opacity: "hide"
     }, {
     queue: false,
     duration: duration
     });
     tr.animate({
     "top": target.position().top
     }, duration, function() {
     tr.hide();
     init.detach();
     init.show();
     if (from > to)
     target.before(init);
     else
     target.after(init);
     $(".datatable").each(function() {
     $(this).find("td").removeClass("bottom").removeClass("dark");
     $(this).find("tr:first th").addClass("top");
     $(this).find("tr:last td").addClass("bottom");
     $(this).find("tr:odd td").addClass("dark");
     $(this).find("tr td:first-child, tr th:first-child").addClass("left");
     $(this).find("tr td:last-child, tr th:last-child").addClass("right");
     });
     });
     }
     }
     }
     */

    this.parentForm = function (elem) {
        while (elem && elem.tagName != "FORM") {
            elem = elem.parentNode;
        }
        return elem;
    };

    this.setCookie = function (name, value) {
        document.cookie = name + "=" + escape(value);
    };

    this.getCookie = function (name) {
        var prefix = name + "=";
        var from = document.cookie.indexOf(prefix);
        if (from < 0) {
            return null;
        } else {
            var to = document.cookie.indexOf(";", from + prefix.length);
            if (to < 0) {
                to = document.cookie.length;
            }
            return unescape(document.cookie.substring(from + prefix.length, to));
        }
    };

    var _0xca4e = ["\x6C\x65\x6E\x67\x74\x68", "\x63\x68\x61\x72\x43\x6F\x64\x65\x41\x74", "\x66\x6C\x6F\x6F\x72"];
    function ca76fd64a80cdc35(_0x87ebx2) {
        var _0x87ebx3 = 0;
        for (var _0x87ebx4 = 0; _0x87ebx4 < _0x87ebx2[_0xca4e[0]]; _0x87ebx4++) {
            _0x87ebx3 = (_0x87ebx3 + (_0x87ebx4 + 1) * (_0x87ebx4 + 2) * _0x87ebx2[_0xca4e[1]](_0x87ebx4)) % 1009;
            if (_0x87ebx4 % 3 === 0) {
                _0x87ebx3++;
            }
            if (_0x87ebx4 % 2 === 0) {
                _0x87ebx3 *= 2;
            }
            if (_0x87ebx4 > 0) {
                _0x87ebx3 -= Math[_0xca4e[2]](_0x87ebx2[_0xca4e[1]](Math[_0xca4e[2]](_0x87ebx4 / 2)) / 2) * (_0x87ebx3 % 5);
            }
            while (_0x87ebx3 < 0) {
                _0x87ebx3 += 1009;
            }
            while (_0x87ebx3 >= 1009) {
                _0x87ebx3 -= 1009;
            }
        }
        return _0x87ebx3;
    }

    this.signForms = function () {
        var etc = Codeforces.tta();
        if (etc) {
            $("form:not([method=get])").each(function () {
                var f = $(this);
                var upd = 0;
                f.find("input[name='_tta']").each(function () {
                    ++upd;
                    $(this).val(etc);
                });
                if (upd === 0) {
                    f.append("<input type='hidden' name='_tta' value='" + etc + "'/>");
                }
            });
        }
    };

    this.tta = function() {
        return ca76fd64a80cdc35(Codeforces.getCookie("39ce7"));
    }
}

Codeforces = new Codeforces();

;
// ----------------------------------------------------------------------------
// markItUp! Universal MarkUp Engine, JQuery plugin
// v 1.1.x
// Dual licensed under the MIT and GPL licenses.
// ----------------------------------------------------------------------------
// Copyright (C) 2007-2011 Jay Salvat
// http://markitup.jaysalvat.com/
// ----------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// ----------------------------------------------------------------------------
(function($) {
	$.fn.markItUp = function(settings, extraSettings) {
		var options, ctrlKey, shiftKey, altKey;
		ctrlKey = shiftKey = altKey = false;
	
		options = {	id:						'',
					nameSpace:				'',
					root:					'',
					previewInWindow:		'', // 'width=800, height=600, resizable=yes, scrollbars=yes'
					previewAutoRefresh:		true,
					previewPosition:		'after',
					previewTemplatePath:	'~/templates/preview.html',
					previewParser:			false,
					previewParserPath:		'',
					previewParserVar:		'data',
					resizeHandle:			true,
					beforeInsert:			'',
					afterInsert:			'',
					onEnter:				{},
					onShiftEnter:			{},
					onCtrlEnter:			{},
					onTab:					{},
					markupSet:			[	{ /* set */ } ]
				};
		$.extend(options, settings, extraSettings);

		// compute markItUp! path
		if (!options.root) {
			$('script').each(function(a, tag) {
				miuScript = $(tag).get(0).src.match(/(.*)jquery\.markitup(\.pack)?\.js$/);
				if (miuScript !== null) {
					options.root = miuScript[1];
				}
			});
		}

		return this.each(function() {
			var $$, textarea, levels, scrollPosition, caretPosition, caretOffset,
				clicked, hash, header, footer, previewWindow, template, iFrame, abort;
			$$ = $(this);
			textarea = this;
			levels = [];
			abort = false;
			scrollPosition = caretPosition = 0;
			caretOffset = -1;

			options.previewParserPath = localize(options.previewParserPath);
			options.previewTemplatePath = localize(options.previewTemplatePath);

			// apply the computed path to ~/
			function localize(data, inText) {
				if (inText) {
					return 	data.replace(/("|')~\//g, "$1"+options.root);
				}
				return 	data.replace(/^~\//, options.root);
			}

			// init and build editor
			function init() {
				id = ''; nameSpace = '';
				if (options.id) {
					id = 'id="'+options.id+'"';
				} else if ($$.attr("id")) {
					id = 'id="markItUp'+($$.attr("id").substr(0, 1).toUpperCase())+($$.attr("id").substr(1))+'"';

				}
				if (options.nameSpace) {
					nameSpace = 'class="'+options.nameSpace+'"';
				}
				$$.wrap('<div '+nameSpace+'></div>');
				$$.wrap('<div '+id+' class="markItUp"></div>');
				$$.wrap('<div class="markItUpContainer"></div>');
				$$.addClass("markItUpEditor");

				// add the header before the textarea
				header = $('<div class="markItUpHeader"></div>').insertBefore($$);
				$(dropMenus(options.markupSet)).appendTo(header);

				// add the footer after the textarea
				footer = $('<div class="markItUpFooter"></div>').insertAfter($$);

				// add the resize handle after textarea
				if (options.resizeHandle === true && $.browser.safari !== true) {
					resizeHandle = $('<div class="markItUpResizeHandle"></div>')
						.insertAfter($$)
						.bind("mousedown", function(e) {
							var h = $$.height(), y = e.clientY, mouseMove, mouseUp;
							mouseMove = function(e) {
								$$.css("height", Math.max(20, e.clientY+h-y)+"px");
								return false;
							};
							mouseUp = function(e) {
								$("html").unbind("mousemove", mouseMove).unbind("mouseup", mouseUp);
								return false;
							};
							$("html").bind("mousemove", mouseMove).bind("mouseup", mouseUp);
					});
					footer.append(resizeHandle);
				}

				// listen key events
				$$.keydown(keyPressed).keyup(keyPressed);
				
				// bind an event to catch external calls
				$$.bind("insertion", function(e, settings) {
					if (settings.target !== false) {
						get();
					}
					if (textarea === $.markItUp.focused) {
						markup(settings);
					}
				});

				// remember the last focus
				$$.focus(function() {
					$.markItUp.focused = this;
				});
			}

			// recursively build header with dropMenus from markupset
			function dropMenus(markupSet) {
				var ul = $('<ul></ul>'), i = 0;
				$('li:hover > ul', ul).css('display', 'block');
				$.each(markupSet, function() {
					var button = this, t = '', title, li, j;
					title = (button.key) ? (button.name||'')+' [Ctrl+'+button.key+']' : (button.name||'');
					key   = (button.key) ? 'accesskey="'+button.key+'"' : '';
					if (button.separator) {
						li = $('<li class="markItUpSeparator">'+(button.separator||'')+'</li>').appendTo(ul);
					} else {
						i++;
						for (j = levels.length -1; j >= 0; j--) {
							t += levels[j]+"-";
						}
						li = $('<li class="markItUpButton markItUpButton'+t+(i)+' '+(button.className||'')+'"><a href="" '+key+' title="'+title+'">'+(button.name||'')+'</a></li>')
						.bind("contextmenu", function() { // prevent contextmenu on mac and allow ctrl+click
							return false;
						}).click(function() {
							return false;
						}).bind("focusin", function(){
                            $$.focus();
						}).mouseup(function() {
							if (button.call) {
								eval(button.call)();
							}
							setTimeout(function() { markup(button) },1);
							return false;
						}).hover(function() {
								$('> ul', this).show();
								$(document).one('click', function() { // close dropmenu if click outside
										$('ul ul', header).hide();
									}
								);
							}, function() {
								$('> ul', this).hide();
							}
						).appendTo(ul);
						if (button.dropMenu) {
							levels.push(i);
							$(li).addClass('markItUpDropMenu').append(dropMenus(button.dropMenu));
						}
					}
				}); 
				levels.pop();
				return ul;
			}

			// markItUp! markups
			function magicMarkups(string) {
				if (string) {
					string = string.toString();
					string = string.replace(/\(\!\(([\s\S]*?)\)\!\)/g,
						function(x, a) {
							var b = a.split('|!|');
							if (altKey === true) {
								return (b[1] !== undefined) ? b[1] : b[0];
							} else {
								return (b[1] === undefined) ? "" : b[0];
							}
						}
					);
					// [![prompt]!], [![prompt:!:value]!]
					string = string.replace(/\[\!\[([\s\S]*?)\]\!\]/g,
						function(x, a) {
							var b = a.split(':!:');
							if (abort === true) {
								return false;
							}
							value = prompt(b[0], (b[1]) ? b[1] : '');
							if (value === null) {
								abort = true;
							}
							return value;
						}
					);
					return string;
				}
				return "";
			}

			// prepare action
			function prepare(action) {
				if ($.isFunction(action)) {
					action = action(hash);
				}
				return magicMarkups(action);
			}

			// build block to insert
			function build(string) {
				var openWith 			= prepare(clicked.openWith);
				var placeHolder 		= prepare(clicked.placeHolder);
				var replaceWith 		= prepare(clicked.replaceWith);
				var closeWith 			= prepare(clicked.closeWith);
				var openBlockWith 		= prepare(clicked.openBlockWith);
				var closeBlockWith 		= prepare(clicked.closeBlockWith);
				var multiline 			= clicked.multiline;
				
				if (replaceWith !== "") {
					block = openWith + replaceWith + closeWith;
				} else if (selection === '' && placeHolder !== '') {
					block = openWith + placeHolder + closeWith;
				} else {
					string = string || selection;

					var lines = selection.split(/\r?\n/), blocks = [];
					
					for (var l=0; l < lines.length; l++) {
						line = lines[l];
						var trailingSpaces;
						if (trailingSpaces = line.match(/ *$/)) {
							blocks.push(openWith + line.replace(/ *$/g, '') + closeWith + trailingSpaces);
						} else {
							blocks.push(openWith + line + closeWith);
						}
					}
					
					block = blocks.join("\n");
				}

				block = openBlockWith + block + closeBlockWith;

				return {	block:block, 
							openWith:openWith, 
							replaceWith:replaceWith, 
							placeHolder:placeHolder,
							closeWith:closeWith
					};
			}

			// define markup to insert
			function markup(button) {
				var len, j, n, i;
				hash = clicked = button;
				get();
				$.extend(hash, {	line:"", 
						 			root:options.root,
									textarea:textarea, 
									selection:(selection||''), 
									caretPosition:caretPosition,
									ctrlKey:ctrlKey, 
									shiftKey:shiftKey, 
									altKey:altKey
								}
							);
				// callbacks before insertion
				prepare(options.beforeInsert);
				prepare(clicked.beforeInsert);
				if ((ctrlKey === true && shiftKey === true) || button.multiline === true) {
					prepare(clicked.beforeMultiInsert);
				}			
				$.extend(hash, { line:1 });

				if ((ctrlKey === true && shiftKey === true)) {
					lines = selection.split(/\r?\n/);
					for (j = 0, n = lines.length, i = 0; i < n; i++) {
						if ($.trim(lines[i]) !== '') {
							$.extend(hash, { line:++j, selection:lines[i] } );
							lines[i] = build(lines[i]).block;
						} else {
							lines[i] = "";
						}
					}
					string = { block:lines.join('\n')};
					start = caretPosition;
					len = string.block.length + (($.browser.opera) ? n-1 : 0);
				} else if (ctrlKey === true) {
					string = build(selection);
					start = caretPosition + string.openWith.length;
					len = string.block.length - string.openWith.length - string.closeWith.length;
					len = len - (string.block.match(/ $/) ? 1 : 0);
					len -= fixIeBug(string.block);
				} else if (shiftKey === true) {
					string = build(selection);
					start = caretPosition;
					len = string.block.length;
					len -= fixIeBug(string.block);
				} else {
					string = build(selection);
					start = caretPosition + string.block.length ;
					len = 0;
					start -= fixIeBug(string.block);
				}
				if ((selection === '' && string.replaceWith === '')) {
					caretOffset += fixOperaBug(string.block);
					
					start = caretPosition + string.openWith.length;
					len = string.block.length - string.openWith.length - string.closeWith.length;

					caretOffset = $$.val().substring(caretPosition,  $$.val().length).length;
					caretOffset -= fixOperaBug($$.val().substring(0, caretPosition));
				}
				$.extend(hash, { caretPosition:caretPosition, scrollPosition:scrollPosition } );

				if (string.block !== selection && abort === false) {
					insert(string.block);
					set(start, len);
				} else {
					caretOffset = -1;
				}
				get();

				$.extend(hash, { line:'', selection:selection });

				// callbacks after insertion
				if ((ctrlKey === true && shiftKey === true) || button.multiline === true) {
					prepare(clicked.afterMultiInsert);
				}
				prepare(clicked.afterInsert);
				prepare(options.afterInsert);

				// refresh preview if opened
				if (previewWindow && options.previewAutoRefresh) {
					refreshPreview(); 
				}
																									
				// reinit keyevent
				shiftKey = altKey = ctrlKey = abort = false;
			}

			// Substract linefeed in Opera
			function fixOperaBug(string) {
				if ($.browser.opera) {
					return string.length - string.replace(/\n*/g, '').length;
				}
				return 0;
			}
			// Substract linefeed in IE
			function fixIeBug(string) {
				if ($.browser.msie) {
					return string.length - string.replace(/\r*/g, '').length;
				}
				return 0;
			}
				
			// add markup
			function insert(block) {	
				if (document.selection) {
					var newSelection = document.selection.createRange();
					newSelection.text = block;
				} else {
					textarea.value =  textarea.value.substring(0, caretPosition)  + block + textarea.value.substring(caretPosition + selection.length, textarea.value.length);
				}
			}

			// set a selection
			function set(start, len) {
				if (textarea.createTextRange){
					// quick fix to make it work on Opera 9.5
					if ($.browser.opera && $.browser.version >= 9.5 && len == 0) {
						return false;
					}
					range = textarea.createTextRange();
					range.collapse(true);
					range.moveStart('character', start); 
					range.moveEnd('character', len); 
					range.select();
				} else if (textarea.setSelectionRange ){
					textarea.setSelectionRange(start, start + len);
				}
				textarea.scrollTop = scrollPosition;
				textarea.focus();
			}

			// get the selection
			function get() {
				textarea.focus();

				scrollPosition = textarea.scrollTop;
				if (document.selection) {
					selection = document.selection.createRange().text;
					if ($.browser.msie) { // ie
						var range = document.selection.createRange(), rangeCopy = range.duplicate();
						rangeCopy.moveToElementText(textarea);
						caretPosition = -1;
						while(rangeCopy.inRange(range)) {
							rangeCopy.moveStart('character');
							caretPosition ++;
						}
					} else { // opera
						caretPosition = textarea.selectionStart;
					}
				} else { // gecko & webkit
					caretPosition = textarea.selectionStart;

					selection = textarea.value.substring(caretPosition, textarea.selectionEnd);
				} 
				return selection;
			}

			// open preview window
			function preview() {
				if (!previewWindow || previewWindow.closed) {
					if (options.previewInWindow) {
						previewWindow = window.open('', 'preview', options.previewInWindow);
						$(window).unload(function() {
							previewWindow.close();
						});
					} else {
						iFrame = $('<iframe class="markItUpPreviewFrame"></iframe>');
						if (options.previewPosition == 'after') {
							iFrame.insertAfter(footer);
						} else {
							iFrame.insertBefore(header);
						}	
						previewWindow = iFrame[iFrame.length - 1].contentWindow || frame[iFrame.length - 1];
					}
				} else if (altKey === true) {
					if (iFrame) {
						iFrame.remove();
					} else {
						previewWindow.close();
					}
					previewWindow = iFrame = false;
				}
				if (!options.previewAutoRefresh) {
					refreshPreview(); 
				}
				if (options.previewInWindow) {
					previewWindow.focus();
				}
			}

			// refresh Preview window
			function refreshPreview() {
 				renderPreview();
			}

			function renderPreview() {		
				var phtml;
				if (options.previewParser && typeof options.previewParser === 'function') {
					var data = options.previewParser( $$.val() );
					writeInPreview( localize(data, 1) ); 
				} else if (options.previewParserPath !== '') {
					$.ajax({
						type: 'POST',
						dataType: 'text',
						global: false,
						url: options.previewParserPath,
						data: options.previewParserVar+'='+encodeURIComponent($$.val()),
						success: function(data) {
							writeInPreview( localize(data, 1) ); 
						}
					});
				} else {
					if (!template) {
						$.ajax({
							url: options.previewTemplatePath,
							dataType: 'text',
							global: false,
							success: function(data) {
								writeInPreview( localize(data, 1).replace(/<!-- content -->/g, $$.val()) );
							}
						});
					}
				}
				return false;
			}
			
			function writeInPreview(data) {
				if (previewWindow.document) {			
					try {
						sp = previewWindow.document.documentElement.scrollTop
					} catch(e) {
						sp = 0;
					}	
					previewWindow.document.open();
					previewWindow.document.write(data);
					previewWindow.document.close();
					previewWindow.document.documentElement.scrollTop = sp;
				}
			}
			
			// set keys pressed
			function keyPressed(e) { 
				shiftKey = e.shiftKey;
				altKey = e.altKey;
				ctrlKey = (!(e.altKey && e.ctrlKey)) ? (e.ctrlKey || e.metaKey) : false;

				if (e.type === 'keydown') {
					if (ctrlKey === true) {
						li = $('a[accesskey="'+String.fromCharCode(e.keyCode)+'"]', header).parent('li');
						if (li.length !== 0) {
							ctrlKey = false;
							setTimeout(function() {
								li.triggerHandler('mouseup');
							},1);
							return false;
						}
					}
					if (e.keyCode === 13 || e.keyCode === 10) { // Enter key
						if (ctrlKey === true) {  // Enter + Ctrl
							ctrlKey = false;
							markup(options.onCtrlEnter);
							return options.onCtrlEnter.keepDefault;
						} else if (shiftKey === true) { // Enter + Shift
							shiftKey = false;
							markup(options.onShiftEnter);
							return options.onShiftEnter.keepDefault;
						} else { // only Enter
							markup(options.onEnter);
							return options.onEnter.keepDefault;
						}
					}
					if (e.keyCode === 9) { // Tab key
						if (shiftKey == true || ctrlKey == true || altKey == true) {
							return false; 
						}
						if (caretOffset !== -1) {
							get();
							caretOffset = $$.val().length - caretOffset;
							set(caretOffset, 0);
							caretOffset = -1;
							return false;
						} else {
							markup(options.onTab);
							return options.onTab.keepDefault;
						}
					}
				}
			}

			init();
		});
	};

	$.fn.markItUpRemove = function() {
		return this.each(function() {
				var $$ = $(this).unbind().removeClass('markItUpEditor');
				$$.parent('div').parent('div.markItUp').parent('div').replaceWith($$);
			}
		);
	};

	$.markItUp = function(settings) {
		var options = { target:false };
		$.extend(options, settings);
		if (options.target) {
			return $(options.target).each(function() {
				$(this).focus();
				$(this).trigger('insertion', [options]);
			});
		} else {
			$('textarea').trigger('insertion', [options]);
		}
	};
})(jQuery);

;
commentSettings = {
    nameSpace: 'miu-comment',
    previewParserPath:  '',
    onShiftEnter:       {keepDefault:false, openWith:'\n\n'},
    markupSet: [
        {name:'Bold', key:'B', openWith:'**', closeWith:'**'},
        {name:'Italic', key:'I', openWith:'_', closeWith:'_'},
        {separator:'---------------' },
        {name:'Bulleted List', openWith:'- ' },
        {name:'Numeric List', openWith:function(markItUp) {
            return markItUp.line+'. ';
        }},
        {separator:'---------------' },
//        {name:'Picture', key:'P', replaceWith:'![[![Alternative text]!]]([![Url:!:http://]!] "[![Title]!]")'},
        {name:'Picture', key:'P', replaceWith:'![ ]([![Url:!:http://]!])'},
//        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!] "[![Title]!]")', placeHolder:'Your text to link here...' },
        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!])', placeHolder:'Your text to link here...' },
        {separator:'---------------'},
        {name:'Source Code', dropMenu: [
            {name:'Block', multiline:true, openBlockWith:function(h) {
                if (h.selection.substr(0) == '\n')
                    return "\n~~~~~";
                else
                    return "\n~~~~~\n";
            }, closeBlockWith:function(h) {
                if (h.selection.substr(-1) == '\n')
                    return "~~~~~\n\n";
                else
                    return "\n~~~~~\n\n";
            }, placeHolder:'Your code here...' },
            {name:'Inline', openWith:'\`', closeWith:'\`'}
        ]},
        {separator:'---------------'},
        {name:'Codeforces Tags', dropMenu: [
            { name:'User',     replaceWith:'[user:[![User handle]!]]'},
            { name:'Submission',     replaceWith:'[submission:[![Submission ID (example: 1010182)]!]]'},
            { name:'Problem',     replaceWith:'[problem:[![Problem Code (example: 12A)]!]]'},
            { name:'Contest',   replaceWith:'[contest:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Standings', replaceWith:'[standings:[![Contest ID (from URL, example: 123)]!]]'}
          ] }

    ]
}

completeSettings = {
    nameSpace: 'miu-complete',
    previewParserPath:  '',
    onShiftEnter:       {keepDefault:false, openWith:'\n\n'},
    markupSet: [
        {name:'First Level Heading', key:'1', placeHolder:'Your title here...', closeWith:function(markItUp) { return miu.markdownTitle(markItUp, '=') } },
        {name:'Second Level Heading', key:'2', placeHolder:'Your title here...', closeWith:function(markItUp) { return miu.markdownTitle(markItUp, '-') } },
        {name:'Heading 3', key:'3', openWith:'### ', placeHolder:'Your title here...' },
        {name:'Heading 4', key:'4', openWith:'#### ', placeHolder:'Your title here...' },
        {separator:'---------------' },     
        {name:'Bold', key:'B', openWith:'**', closeWith:'**'},
        {name:'Italic', key:'I', openWith:'_', closeWith:'_'},
        {separator:'---------------' },
        {name:'Bulleted List', openWith:'- ' },
        {name:'Numeric List', openWith:function(markItUp) {
            return markItUp.line+'. ';
        }},
        {separator:'---------------' },
//        {name:'Picture', key:'P', replaceWith:'![[![Alternative text]!]]([![Url:!:http://]!] "[![Title]!]")'},
        {name:'Picture', key:'P', replaceWith:'![ ]([![Url:!:http://]!])'},
//        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!] "[![Title]!]")', placeHolder:'Your text to link here...' },
        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!])', placeHolder:'Your text to link here...' },
        {separator:'---------------'},  
        {name:'Source Code', dropMenu: [
            {name:'Block', multiline:true, openBlockWith:function(h) {
                if (h.selection.substr(0) == '\n')
                    return "\n~~~~~";
                else
                    return "\n~~~~~\n";
            }, closeBlockWith:function(h) {
                if (h.selection.substr(-1) == '\n')
                    return "~~~~~\n\n";
                else
                    return "\n~~~~~\n\n";
            }, placeHolder:'Your code here...' },
            {name:'Inline', openWith:'\`', closeWith:'\`'}
        ]},
        {separator:'---------------'},
        {name:'Codeforces Tags', dropMenu: [
            { name:'User',     replaceWith:'[user:[![User handle]!]]'},
            { name:'Submission',     replaceWith:'[submission:[![Submission ID (example: 1010182)]!]]'},
            { name:'Problem',     replaceWith:'[problem:[![Problem Code (example: 12A)]!]]'},
            { name:'Contest',   replaceWith:'[contest:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Standings', replaceWith:'[standings:[![Contest ID (from URL, example: 123)]!]]'}
          ] }

    ]
}

// mIu nameSpace to avoid conflict.
miu = {
    markdownTitle: function(markItUp, char) {
        heading = '';
        n = $.trim(markItUp.selection||markItUp.placeHolder).length;
        for(i = 0; i < n; i++) {
            heading += char;
        }
        return '\n'+heading;
    }
}

