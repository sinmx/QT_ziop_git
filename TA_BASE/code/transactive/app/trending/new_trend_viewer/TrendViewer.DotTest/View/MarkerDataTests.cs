using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using System;
using System.Windows.Forms;
using TrendViewer.DotTest.Factories.View;
using TrendViewer.View;
using Entity.Trending;
using TrendViewer.Controller;

namespace TrendViewer.DotTest.View
{
    [TestFixture()]
    public class MarkerDataTests
    {
        private MarkerData markerData;

        [TestFixtureSetUp]
        public void FixtureSetUp()
        {
            markerData = new MarkerData();
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+Sbvnw", "+Wf6lw")]
        public void TestSetFormType01()
        {
            using (MarkerData markerData = MarkerDataFactory.CreateMarkerData01())
            {
                FormType type = FormType.Edit;
                markerData.SetFormType(type);

            }
        }

//         [TestCaseUnverified("Test case not verified")]
//         [TestCaseAutogenerated]
//         [TestAuthor("user")]
//         [Test]
//         [HashCode("/hbmxg", "+CuhUQ")]
//         public void TestMarkerDataConstructor01()
//         {
//             MarkerData markerData = new MarkerData();
// 
//         }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+540TQ", "/A3rkw")]
        public void TestTranslateCaption01()
        {
            using (MarkerData markerData = MarkerDataFactory.CreateMarkerData01())
            {
                markerData.SetFormType(FormType.Add);
                markerData.TranslateCaption();
                markerData.SetFormType(FormType.Edit);
                markerData.TranslateCaption();
 
            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+BpeOA", "/fazQQ")]
        public void TestGetNewMarker01()
        {
            using (MarkerData markerData = MarkerDataFactory.CreateMarkerData01())
            {
                EtyMarker etyMarker = markerData.GetNewMarker();
   
            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+Y0sqw", "/EdKZQ")]
        public void TestGetMarkerName01()
        {
            using (MarkerData markerData = MarkerDataFactory.CreateMarkerData01())
            {
                string str = markerData.GetMarkerName();

            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/AyBrw", "+UgRug")]
        public void TestDispose01()
        {
            using (MarkerData markerData = MarkerDataFactory.CreateMarkerData01())
            {
                bool disposing = true;
                Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
                markerDataAccessor.SetField("components", new System.ComponentModel.Container());
                markerDataAccessor.Call("Dispose", disposing);

            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/xiTRQ", "+WJM2g")]
        public void TestInitializeComponent01()
        {
            using (MarkerData markerData = MarkerDataFactory.CreateMarkerData01())
            {
                Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
                markerDataAccessor.Call("InitializeComponent");

            }
        }

        [Test]
        public void TestAttacheListener()
        {
            MarkerDataController ctl = new MarkerDataController();
            markerData.SetFormType(FormType.Add);
            markerData.AttachListener(ctl);
            markerData.SetFormType(FormType.Edit);
            markerData.AttachListener(ctl);
        }

        [Test]
        public void TestMarkerData_Load01()
        {
            markerData.SetFormType(FormType.Add);
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.Call("MarkerData_Load", null, null);

            MarkerDataController ctl = new MarkerDataController();
            Accessor ctlAccessor = ReflectionAccessor.Wrap(ctl);
            EtyMarker ety = new EtyMarker();
            ety.MarkerBColor = "-32704";
            ety.MarkerFColor = "-32704";
            ety.MarkerValue = 2;
            ety.MarkerWidth = 2;
            ctlAccessor.SetField("m_marker",ety);
            markerDataAccessor.SetField("m_controller", ctl);
            markerData.SetFormType(FormType.Edit);
            markerDataAccessor.Call("MarkerData_Load", null, null);
        }

        [Test]
        public void TestMarkerData_Load02()
        {
            markerData.SetFormType(FormType.Edit);
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.Call("MarkerData_Load", null, null);
            //type: edit, ctl.getMarker() throw exception
        }

        [Test]
        public void TestfontColorCmd_Click01()
        {
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.Call("fontColorCmd_Click", null, null);
        }
        [Test]
        public void TestfontColorCmd_Click02()
        {
            //Exception
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.SetField("colorDialog1", null);
            markerDataAccessor.Call("fontColorCmd_Click", null, null);
        }
        [Test]
        public void TestbackColorCmd_Click01()
        {
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.Call("backColorCmd_Click", null, null);
        }
        [Test]
        public void TestbackColorCmd_Click02()
        {
            //Exception
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.SetField("colorDialog1", null);
            markerDataAccessor.Call("backColorCmd_Click", null, null);
        }

        [Test]
        public void TestMarkerData_Paint()
        {
            Accessor markerDataAccessor = ReflectionAccessor.Wrap(markerData);
            markerDataAccessor.Call("MarkerData_Paint", null, null);
        }
    }
}
