# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _libcvautomation
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


LIBCVAUTOMATION_VERSION = _libcvautomation.LIBCVAUTOMATION_VERSION
LIBCVAUTOMATION_BUGREPORT = _libcvautomation.LIBCVAUTOMATION_BUGREPORT
class cvaPoint(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, cvaPoint, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, cvaPoint, name)
    __repr__ = _swig_repr
    __swig_setmethods__["x"] = _libcvautomation.cvaPoint_x_set
    __swig_getmethods__["x"] = _libcvautomation.cvaPoint_x_get
    if _newclass:x = property(_libcvautomation.cvaPoint_x_get, _libcvautomation.cvaPoint_x_set)
    __swig_setmethods__["y"] = _libcvautomation.cvaPoint_y_set
    __swig_getmethods__["y"] = _libcvautomation.cvaPoint_y_get
    if _newclass:y = property(_libcvautomation.cvaPoint_y_get, _libcvautomation.cvaPoint_y_set)
    def __init__(self, *args): 
        this = _libcvautomation.new_cvaPoint(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _libcvautomation.delete_cvaPoint
    __del__ = lambda self : None;
cvaPoint_swigregister = _libcvautomation.cvaPoint_swigregister
cvaPoint_swigregister(cvaPoint)

class cvautomationList(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, cvautomationList, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, cvautomationList, name)
    __repr__ = _swig_repr
    __swig_setmethods__["cvaImage"] = _libcvautomation.cvautomationList_cvaImage_set
    __swig_getmethods__["cvaImage"] = _libcvautomation.cvautomationList_cvaImage_get
    if _newclass:cvaImage = property(_libcvautomation.cvautomationList_cvaImage_get, _libcvautomation.cvautomationList_cvaImage_set)
    __swig_setmethods__["fileName"] = _libcvautomation.cvautomationList_fileName_set
    __swig_getmethods__["fileName"] = _libcvautomation.cvautomationList_fileName_get
    if _newclass:fileName = property(_libcvautomation.cvautomationList_fileName_get, _libcvautomation.cvautomationList_fileName_set)
    __swig_setmethods__["resultPoint"] = _libcvautomation.cvautomationList_resultPoint_set
    __swig_getmethods__["resultPoint"] = _libcvautomation.cvautomationList_resultPoint_get
    if _newclass:resultPoint = property(_libcvautomation.cvautomationList_resultPoint_get, _libcvautomation.cvautomationList_resultPoint_set)
    __swig_setmethods__["searchMethod"] = _libcvautomation.cvautomationList_searchMethod_set
    __swig_getmethods__["searchMethod"] = _libcvautomation.cvautomationList_searchMethod_get
    if _newclass:searchMethod = property(_libcvautomation.cvautomationList_searchMethod_get, _libcvautomation.cvautomationList_searchMethod_set)
    __swig_setmethods__["tolerance"] = _libcvautomation.cvautomationList_tolerance_set
    __swig_getmethods__["tolerance"] = _libcvautomation.cvautomationList_tolerance_get
    if _newclass:tolerance = property(_libcvautomation.cvautomationList_tolerance_get, _libcvautomation.cvautomationList_tolerance_set)
    def __init__(self, *args): 
        this = _libcvautomation.new_cvautomationList(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _libcvautomation.delete_cvautomationList
    __del__ = lambda self : None;
cvautomationList_swigregister = _libcvautomation.cvautomationList_swigregister
cvautomationList_swigregister(cvautomationList)

matchSubImage = _libcvautomation.matchSubImage
matchSubImage_center = _libcvautomation.matchSubImage_center
matchSubImage_location = _libcvautomation.matchSubImage_location
matchSubImage_location_center = _libcvautomation.matchSubImage_location_center
matchSubImage_a = _libcvautomation.matchSubImage_a
matchSubImage_a_center = _libcvautomation.matchSubImage_a_center
matchSubImage_a_location = _libcvautomation.matchSubImage_a_location
matchSubImage_a_location_center = _libcvautomation.matchSubImage_a_location_center
cvaOpenDisplay = _libcvautomation.cvaOpenDisplay
cvaCloseDisplay = _libcvautomation.cvaCloseDisplay
matchSubImage_X11 = _libcvautomation.matchSubImage_X11
matchSubImage_X11_center = _libcvautomation.matchSubImage_X11_center
matchSubImage_X11_location = _libcvautomation.matchSubImage_X11_location
matchSubImage_X11_location_center = _libcvautomation.matchSubImage_X11_location_center
COMMAND_STR_LEN = _libcvautomation.COMMAND_STR_LEN
xte_XTestSupported = _libcvautomation.xte_XTestSupported
xte_mouseLocation = _libcvautomation.xte_mouseLocation
xte_clickMouse = _libcvautomation.xte_clickMouse
xte_clickMouseXY = _libcvautomation.xte_clickMouseXY
xte_clickMouseRXY = _libcvautomation.xte_clickMouseRXY
xte_clickMouseImage = _libcvautomation.xte_clickMouseImage
xte_clickMouseImage_location = _libcvautomation.xte_clickMouseImage_location
xte_clickMouseImage_center = _libcvautomation.xte_clickMouseImage_center
xte_clickMouseImage_location_center = _libcvautomation.xte_clickMouseImage_location_center
xte_hoverMouseXY = _libcvautomation.xte_hoverMouseXY
xte_hoverMouseRXY = _libcvautomation.xte_hoverMouseRXY
xte_hoverMouseImage = _libcvautomation.xte_hoverMouseImage
xte_hoverMouseImage_location = _libcvautomation.xte_hoverMouseImage_location
xte_hoverMouseImage_center = _libcvautomation.xte_hoverMouseImage_center
xte_hoverMouseImage_location_center = _libcvautomation.xte_hoverMouseImage_location_center
xte_mouseDown = _libcvautomation.xte_mouseDown
xte_mouseUp = _libcvautomation.xte_mouseUp
xte_mouseJiggle = _libcvautomation.xte_mouseJiggle
xte_mouseScrollUp = _libcvautomation.xte_mouseScrollUp
xte_mouseScrollDown = _libcvautomation.xte_mouseScrollDown
xte_clickKey = _libcvautomation.xte_clickKey
xte_clickKeyStr = _libcvautomation.xte_clickKeyStr
xte_keyDown = _libcvautomation.xte_keyDown
xte_keyUp = _libcvautomation.xte_keyUp
xte_waitForImage = _libcvautomation.xte_waitForImage
xte_waitForImage_location = _libcvautomation.xte_waitForImage_location
xte_waitForImage_center = _libcvautomation.xte_waitForImage_center
xte_waitForImage_location_center = _libcvautomation.xte_waitForImage_location_center
xte_commandString = _libcvautomation.xte_commandString


