using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using System;
using TrendViewer;
using TrendViewer.Properties;

namespace TrendViewer.DotTest
{
    [TestFixture()]
    public class ProgramTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+vvPMw", "+FAqmQ")]
        public void TestMain01()
        {
            string[] args = new string[1];
            args[0] = "view-0";
            StaticAccessor programAccessor = ReflectionAccessor.Wrap(typeof(Program));
            programAccessor.Call("Main", args); //timeout

        }

        [Test]
        public void TestMain02()
        {
            //Exception
            string[] args = new string[1];
            args[0] = "view-0";
            StaticAccessor programAccessor = ReflectionAccessor.Wrap(typeof(Program));
            programAccessor.Call("Main", args); //timeout

        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+3zvHA", "+OEpcQ")]
        public void TestOpenEvent01()
        {
            int desiredAccess = 1;
            bool inheritHandle = false;
            string name = string.Empty;
          //  IntPtr intPtr = Program.OpenEvent(desiredAccess, inheritHandle, name);
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+rPAJw", "+0+RCw")]
        public void TestCreateWin32EventAndSetLogFile01()
        {
            StaticAccessor programAccessor = ReflectionAccessor.Wrap(typeof(Program));
            string str = (string)programAccessor.Call("CreateWin32EventAndSetLogFile");

        }

        [Test]
        public void TestCreateWin32EventAndSetLogFile02()
        {
            //todo:stub: hEvent = OpenEvent(0x1F0003, false, eventName)  hEvent!=IntPtr.Zero
            //todo:stub: CloseHandle do nothing
            StaticAccessor programAccessor = ReflectionAccessor.Wrap(typeof(Program));
            string str = (string)programAccessor.Call("CreateWin32EventAndSetLogFile");

        }

        [Test]
        public void TestCreateWin32EventAndSetLogFile03()
        {
            //stub:LogHelper.setLogFile throw exception
            StaticAccessor programAccessor = ReflectionAccessor.Wrap(typeof(Program));
            string str = (string)programAccessor.Call("CreateWin32EventAndSetLogFile");
        }

        [Test]
        public void TestPropertiesSettings()
        {
//             TrendViewer.Properties.Settings s = TrendViewer.Properties.Settings.Default;
// 
//             TrendViewer.Properties.Resources r = new TrendViewer.Properties.Resources();
//             Resources.Culture = Resources.Culture;
//             System.Drawing.Bitmap bm = Resources.Find_in_folder_16_;
//             bm = Resources.btn_garbage;
//             bm = Resources.nav_icon_detreport;
           
        }
    }
}