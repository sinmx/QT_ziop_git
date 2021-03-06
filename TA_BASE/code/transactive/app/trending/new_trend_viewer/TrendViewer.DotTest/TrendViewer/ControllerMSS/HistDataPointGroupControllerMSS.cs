using System;
using Dottest.Framework;
using TrendViewer.DotTest.Controller;

namespace TrendViewer.ControllerMSS
{
    [MethodSpecificStubsAssemblyAttribute("TrendViewer")]
    [MethodSpecificStubsClassAttribute("TrendViewer.Controller.HistDataPointGroupController")]
    public class HistDataPointGroupControllerMSS
    {
        [MethodSpecificStubsMethod("TrendViewer.Controller.HistDataPointGroupController.SetFormType(TrendViewer.View.FormType)")]
        public static void SetFormTypeMSS(
            /*TrendViewer.Controller.HistDataPointGroupController*/ object target,
        TrendViewer.View.FormType type)
        {
            object result;
            if (TestSpecificStubsUtil.RunTestSpecificStub(System.Reflection.MethodBase.GetCurrentMethod(), new object[] { target, type }, out result))
            {
                return;
            }
            else
            {
                Helper.CallMethod(target, "SetFormType", new object[] { type });
            }
        }

        [TestSpecificStub("TrendViewer.Controller.HistDataPointGroupController.SetFormType(TrendViewer.View.FormType)")]
        // TODO: uncomment the following attribute and provide a test fixture and a name of its test
        [TestSpecificStubContext(typeof(HistDataPointListControllerTests), "TestSaveHistDataPoint02")]
        public static void SetFormTypeTSS(
            /*TrendViewer.Controller.HistDataPointGroupController*/ object target,
        TrendViewer.View.FormType type)
        {
            Exception e = new Exception();
            throw e;
        }

    }
}

