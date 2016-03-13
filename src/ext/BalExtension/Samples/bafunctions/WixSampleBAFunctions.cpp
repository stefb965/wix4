//-------------------------------------------------------------------------------------------------
// <copyright file="WixSampleBAFunctions.cpp" company="Outercurve Foundation">
//   Copyright (c) 2004, Outercurve Foundation.
//   This software is released under Microsoft Reciprocal License (MS-RL).
//   The license and further copyright text can be found in the file
//   LICENSE.TXT at the root directory of the distribution.
// </copyright>
//-------------------------------------------------------------------------------------------------


#include "precomp.h"
#include "BalBaseBAFunctions.h"
#include "BalBaseBAFunctionsProc.h"

class CWixSampleBAFunctions : public CBalBaseBAFunctions
{
public:
    STDMETHODIMP OnDetect()
    {
        HRESULT hr = S_OK;

        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running detect BA function");

        //-------------------------------------------------------------------------------------------------
        // YOUR CODE GOES HERE
        BalExitOnFailure(hr, "Change this message to represent real error handling.");
        //-------------------------------------------------------------------------------------------------

    LExit:
        return hr;
    }


    STDMETHODIMP OnPlan()
    {
        HRESULT hr = S_OK;

        BalLog(BOOTSTRAPPER_LOG_LEVEL_STANDARD, "Running plan BA function");

        //-------------------------------------------------------------------------------------------------
        // YOUR CODE GOES HERE
        BalExitOnFailure(hr, "Change this message to represent real error handling.");
        //-------------------------------------------------------------------------------------------------

    LExit:
        return hr;
    }

public:
    //
    // Constructor - initialize member variables.
    //
    CWixSampleBAFunctions(
        __in HMODULE hModule,
        __in IBootstrapperEngine* pEngine,
        __in const BA_FUNCTIONS_CREATE_ARGS* pArgs
        ) : CBalBaseBAFunctions(hModule, pEngine, pArgs)
    {
    }

    //
    // Destructor - release member variables.
    //
    ~CWixSampleBAFunctions()
    {
    }
};


HRESULT WINAPI CreateBAFunctions(
    __in HMODULE hModule,
    __in const BA_FUNCTIONS_CREATE_ARGS* pArgs,
    __inout BA_FUNCTIONS_CREATE_RESULTS* pResults
    )
{
    HRESULT hr = S_OK;
    CWixSampleBAFunctions* pBAFunctions = NULL;
    IBootstrapperEngine* pEngine = NULL;

    // This is required to enable logging functions.
    hr = BalInitializeFromCreateArgs(pArgs->pBootstrapperCreateArgs, &pEngine);
    ExitOnFailure(hr, "Failed to initialize Bal.");

    pBAFunctions = new CWixSampleBAFunctions(hModule, pEngine, pArgs);
    ExitOnNull(pBAFunctions, hr, E_OUTOFMEMORY, "Failed to create new CWixSampleBAFunctions object.");

    pResults->pfnBAFunctionsProc = BalBaseBAFunctionsProc;
    pResults->pvBAFunctionsProcContext = pBAFunctions;
    pResults->pBAFunctions = pBAFunctions;
    pBAFunctions = NULL;

LExit:
    ReleaseObject(pBAFunctions);
    ReleaseObject(pEngine);

    return hr;
}
