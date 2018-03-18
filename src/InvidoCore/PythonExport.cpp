/*
    Invido
    Copyright (C) 2005  Igor Sarzi Sartori

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Igor Sarzi Sartori
    www.invido.it
    6colpiunbucosolo@gmx.net
*/

// PythonExport.cpp

#include "StdAfx.h"
#include "win_type_global.h"


#ifdef NOPYTHON

    // python is not used on compile time

    // dummy notification
    void NotifyCustomControlEvent(int iEvent){}
    void NotifyAlgEvent(int iAlgIndex, int iEvent){}

#else

//use python script engine

#include <string>
#include "cSettings.h"

#include <fcntl.h>


#include <Python.h>
#include "resource.h"

#include "cInvidoCoreEngine.h"
#include <iostream>
#include <fstream>
#include "TraceService.h"

// script callback
static PyObject* g_Script_callback = NULL;

// python control callback
static PyObject* g_PytCtrl_callback = NULL;

// invido core object
cInvidoCore*  g_pInvidoCore = 0;

// algorithm callbacks
static PyObject* g_cbAlgNtfyer[MAX_NUM_PLAYER] = {NULL,NULL,NULL,NULL};

////////////////////////////////////////
//       Invido_CheckVersion
/*! 
// \param PyObject *self : 
// \param PyObject *args : 
*/
static PyObject* Invido_CheckVersion(PyObject *self, PyObject *args)
{
    if(!PyArg_ParseTuple(args, ":CheckVersion"))
        return NULL;
    std::string strTmp;
    std::string strVer;

    strVer = "0.5"; 

    return Py_BuildValue("s", strVer.c_str());
}



////////////////////////////////////////
//       Invido_set_callbackCtrl
/*! Set Callback function called from InvidoCore
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_set_callbackCtrl(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    PyObject *temp;

    if (PyArg_ParseTuple(args, "O:set_callbackCtrl", &temp)) 
    {
        if (!PyCallable_Check(temp)) 
        {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_XINCREF(temp);         /* Add a reference to new callback */
        Py_XDECREF(g_PytCtrl_callback);  /* Dispose of previous callback */
        g_PytCtrl_callback = temp;       /* Remember new callback */
        /* Boilerplate to return "None" */
        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}

////////////////////////////////////////
//       Invido_set_cbAlgPlayer
/*! 
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_set_cbAlgPlayer(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    PyObject *temp;
    int iIndex = 0;

    if (PyArg_ParseTuple(args, "iO:Invido_set_cbAlgPlayer", &iIndex, &temp)) 
    {
        if (!PyCallable_Check(temp)) 
        {
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        if (iIndex >= 0 && iIndex < MAX_NUM_PLAYER)
        {
            // index admitted
            Py_XINCREF(temp);         /* Add a reference to new callback */
            Py_XDECREF(g_cbAlgNtfyer[iIndex]);  /* Dispose of previous callback */
            g_cbAlgNtfyer[iIndex] = temp;       /* Remember new callback */
            /* Boilerplate to return "None" */
            Py_INCREF(Py_None);
            result = Py_None;
        }
        
    }
    return result;
}

////////////////////////////////////////
//       Invido_setPlayerDeck
/*! Override player deck 
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_setPlayerDeck(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    int iPlayerIx;
    int iCard1;
    int iCard2;
    int iCard3;

    if (PyArg_ParseTuple(args, "iiii", &iPlayerIx, &iCard1, &iCard2, &iCard3)) 
    {
        ASSERT(g_pInvidoCore);
        if (g_pInvidoCore)
        {
            g_pInvidoCore->Script_OverrideDeck(iPlayerIx, iCard1, iCard2, iCard3); 
        }

        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}


////////////////////////////////////////
//       Invido_Say
/*! Script say something
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_Say(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    int iPlayerIx;
    int iSay;
    
    if (PyArg_ParseTuple(args, "ii", &iPlayerIx, &iSay)) 
    {
        ASSERT(g_pInvidoCore);
        if (g_pInvidoCore)
        {
            g_pInvidoCore->Script_Say(iPlayerIx, (eSayPlayer)iSay); 
        }

        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}


////////////////////////////////////////
//       Invido_Play
/*! The algorith play something
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_Play(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    int iPlayerIx;
    int iCardIndex;
    
    if (PyArg_ParseTuple(args, "ii", &iPlayerIx, &iCardIndex)) 
    {
        ASSERT(g_pInvidoCore);
        if (g_pInvidoCore)
        {
            CardSpec Card;
            Card.SetCardIndex(iCardIndex); 
            g_pInvidoCore->Script_Play(iPlayerIx, Card); 
        }

        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}



////////////////////////////////////////
//       Invido_match_end
/*! Terminate the match
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_match_end(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    
    ASSERT(g_pInvidoCore);
    if (g_pInvidoCore)
    {
        g_pInvidoCore->Script_MatchEnd(); 
    }

    Py_INCREF(Py_None);
    result = Py_None;

    return result;
}


////////////////////////////////////////
//       Invido_startPlayer
/*! 
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_startPlayer(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    int iPlayerIx;
    
    if (PyArg_ParseTuple(args, "i", &iPlayerIx)) 
    {
        ASSERT(g_pInvidoCore);
        if (g_pInvidoCore)
        {
            g_pInvidoCore->Script_SetStartPlayer(iPlayerIx); 
        }

        Py_INCREF(Py_None);
        result = Py_None;
    }
    return result;
}

////////////////////////////////////////
//       Invido_checkRes
/*! 
// \param PyObject *dummy : 
// \param PyObject *args : 
*/
static PyObject* Invido_checkRes(PyObject *dummy, PyObject *args)
{
    PyObject *result = NULL;
    int iTypeOfItem  = 0;
    int iExpectedVal = 0;
    int iParam1 = 0;
    int iRetRes = 0;
    
    if (PyArg_ParseTuple(args, "iii", &iTypeOfItem, &iParam1, &iExpectedVal)) 
    {
        ASSERT(g_pInvidoCore);
        if (g_pInvidoCore)
        {
            iRetRes = g_pInvidoCore->Script_CheckResult(iTypeOfItem, iParam1, iExpectedVal ); 
            
        }
    }
    result = Py_BuildValue("i", iRetRes);

    return result;
}

// collection of exported functions
static PyMethodDef staPcsimEmbMethods[] = 
{
    {"CheckVersion", Invido_CheckVersion, METH_VARARGS,
     "Return the program version number."},
    {"set_callbackCtrl", Invido_set_callbackCtrl, METH_VARARGS,
    "Set the game loop callback."},
    {"setPlayerDeck", Invido_setPlayerDeck, METH_VARARGS,
    "Set the deck of a player."},
    {"Say", Invido_Say, METH_VARARGS,
    "Player say something."},
    {"Play", Invido_Play, METH_VARARGS,
    "Player play something."},
    {"set_cbAlgPlayer", Invido_set_cbAlgPlayer, METH_VARARGS,
    "Set the algorithm callback."},
    {"match_end", Invido_match_end, METH_VARARGS,
    "Terminate the match."},
    {"startPlayer", Invido_startPlayer, METH_VARARGS,
    "Set the Start player."},
    {"checkRes", Invido_checkRes, METH_VARARGS,
    "Check the result of an item."},
    {NULL, NULL, 0, NULL}
    
};



////////////////////////////////////////
//       InitExport
/*! Export the module
*/
void InitExport()
{
    // export the module and methods
    Py_InitModule("Invido", staPcsimEmbMethods);
}




////////////////////////////////////////
//       NotifyCustomControlEvent
/*! Notify to python script a custom control event 
// \param int iEvent : event to be notified
*/
void NotifyCustomControlEvent(int iEvent)
{
    if (g_Options.All.bUsePython )
    {
        if (g_PytCtrl_callback)
        {
            int arg;
            PyObject *arglist;
            PyObject *result;
            arg = iEvent;
    
            arglist = Py_BuildValue("(i)", arg);
        
            result = PyEval_CallObject(g_PytCtrl_callback, arglist);
    
            Py_DECREF(arglist); 
        }
        else
        {
            std::cout << "*** ERR script not initialized or game-loop callback not set\n";
        }
    }
}


////////////////////////////////////////
//       NotifyAlgEvent
/*! Notify an event to the algorithm handler in script
// \param int iAlgIndex : algorithm index (0 = hmi player, 1 = cpu)
// \param int iEvent : event to notify
*/
void NotifyAlgEvent(int iAlgIndex, int iEvent)
{
    if (g_Options.All.bUsePython )
    {
        if (iAlgIndex >= 0 && iAlgIndex < MAX_NUM_PLAYER)
        {
            if ( g_cbAlgNtfyer[iAlgIndex] )
            {
                // calback is set
                int arg;
                PyObject *arglist;
                PyObject *result;
                arg = iEvent;
    
                arglist = Py_BuildValue("(i)", arg);
        
                result = PyEval_CallObject(g_cbAlgNtfyer[iAlgIndex], arglist);
    
                Py_DECREF(arglist); 
            }
            else
            {
                TraceService* pTracer = TraceService::Instance(); 
                pTracer->AddNewEntry(1, 51, EntryTraceDetail::TR_ERR, __FILE__, __LINE__);
                pTracer->AddCommentToLastEntry("Callback not set %d", iAlgIndex); 
            }
        }
        else
        {
            TraceService* pTracer = TraceService::Instance(); 
            pTracer->AddNewEntry(1, 50, EntryTraceDetail::TR_ERR, __FILE__, __LINE__);
            pTracer->AddCommentToLastEntry("iAlgIndex = %d not right", iAlgIndex); 
        }
    }
}


////////////////////////////////////////
//       ExportFinalize
/*! Python session is ended
*/
void ExportFinalize()
{
    g_Script_callback = 0;
    g_PytCtrl_callback = 0;
    for (int i = 0; i < MAX_NUM_PLAYER; i++)
    {
        g_cbAlgNtfyer[i] = 0;
    }
}


#endif


