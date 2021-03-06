using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using System;
using System.Windows.Forms;
using TrendViewer.DotTest.Factories.View;
using TrendViewer.View;
using TrendViewer.Controller;
using Entity.Trending;
using System.Collections.Generic;

namespace TrendViewer.DotTest.View
{
    [TestFixture()]
    public class MarkerListTests
    {
        private MarkerList markerList;
        
        [TestFixtureSetUp]
        public void FixtureSetUp()
        {
            markerList = new MarkerList();
            MarkerListController ctl = new MarkerListController();
            ctl.initMarkerTable();

            List<EtyMarker> list = new List<EtyMarker>();
            ctl.SetMarkerTable(list);
            ctl.SetGrpName("Test_GrpName");

            markerList.AttachController(ctl);
            ctl.AttachCallBack(null, markerList);

        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/mfVuQ", "/QVpjQ")]
        public void TestDispose01()
        {
            using (MarkerList markerList = MarkerListFactory.CreateMarkerList01())
            {
                bool disposing = false;
                Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
                markerListAccessor.Call("Dispose", disposing);

            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("++5HiA", "+orUmA")]
        public void TestInitializeComponent01()
        {
            using (MarkerList markerList = MarkerListFactory.CreateMarkerList01())
            {
                Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
                markerListAccessor.Call("InitializeComponent");

            }
        }

//         [TestCaseUnverified("Test case not verified")]
//         [TestCaseAutogenerated]
//         [TestAuthor("user")]
//         [Test]
//         [HashCode("+KkwTA", "/T16qw")]
//         public void TestMarkerListConstructor01()
//         {
//             MarkerList markerList = new MarkerList();
// 
//         }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+8zkmQ", "/z18cA")]
        public void TestTranslateCaption01()
        {
            using (MarkerList markerList = MarkerListFactory.CreateMarkerList01())
            {
                markerList.TranslateCaption();

            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/XJFRg", "/HNaFQ")]
        public void TestInitializeDataMarkerListDataGridView01()
        {
            using (MarkerList markerList = MarkerListFactory.CreateMarkerList01())
            {
                Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
                markerListAccessor.Call("InitializeDataMarkerListDataGridView");

            }
        }

        [Test]
        public void TestInitializeDataMarkerListDataGridView02()
        {
            //Exception caught
            using (MarkerList markerList = MarkerListFactory.CreateMarkerList01())
            {
                Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
                markerListAccessor.Call("InitializeDataMarkerListDataGridView");

            }
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/RFZCQ", "+zABqg")]
        public void TestPopulateDataMarkerListDataGridView01()
        {
            using (MarkerList markerList = MarkerListFactory.CreateMarkerList01())
            {
                int mode = 1;
                markerList.PopulateDataMarkerListDataGridView(mode);

            }
        }

        [Test]
        public void TestDataMarkerViewer_Paint()
        {
            Accessor viewAccessor = ReflectionAccessor.Wrap(markerList);
            viewAccessor.Call("DataMarkerViewer_Paint", null, null);
        }


        [Test]
        public void TestDataMarkerViewer_Load01()
        {
            Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
            markerListAccessor.Call("DataMarkerViewer_Load", null, null);
        }

        [Test]
        public void TestDataMarkerViewer_Load02()
        {
            //Exception caught
            Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
            markerListAccessor.Call("DataMarkerViewer_Load", null, null);
        }

        [Test]
        public void TestPopulateDataMarkerListDataGridView_GetMarkNameByRowIndex()
        {
            markerList.PopulateDataMarkerListDataGridView(1);
            markerList.GetMarkNameByRowIndex(10);
            MarkerListController ctl = (MarkerListController)(markerList.getController());

            EtyMarker marker1 = new EtyMarker();
            marker1.MarkerName = "a1";
            ctl.AddMarkerToList(marker1);

            markerList.PopulateDataMarkerListDataGridView(1);
            markerList.GetMarkNameByRowIndex(0);

            EtyMarker marker2 = new EtyMarker();
            marker2.MarkerName = "a2";
            ctl.AddMarkerToList(marker2);
            EtyMarker marker3 = new EtyMarker();
            marker3.MarkerName = "a3";
            ctl.AddMarkerToList(marker3);
            EtyMarker marker4 = new EtyMarker();
            marker4.MarkerName = "a4";
            ctl.AddMarkerToList(marker4);
            EtyMarker marker5 = new EtyMarker();
            marker5.MarkerName = "a5";
            ctl.AddMarkerToList(marker5);
            EtyMarker marker6 = new EtyMarker();
            marker6.MarkerName = "a6";
            ctl.AddMarkerToList(marker6);
            EtyMarker marker7 = new EtyMarker();
            marker7.MarkerName = "a7";
            ctl.AddMarkerToList(marker7);
            EtyMarker marker8 = new EtyMarker();
            marker8.MarkerName = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
            ctl.AddMarkerToList(marker8);

            markerList.PopulateDataMarkerListDataGridView(1);

        }

        [Test]
        public void TestfirstdataMarkerListDataGridView_Click_nextdataMarkerListDataGridView_Click()
        {
            Accessor markerListAccessor = ReflectionAccessor.Wrap(markerList);
            markerListAccessor.Call("firstdataMarkerListDataGridView_Click", null, null);

            markerList.PopulateDataMarkerListDataGridView(1);
            MarkerListController ctl = (MarkerListController)(markerList.getController());
            EtyMarker marker9 = new EtyMarker();
            marker9.MarkerName = "a9";
            ctl.AddMarkerToList(marker9);
            markerList.PopulateDataMarkerListDataGridView(2);

            markerListAccessor.Call("nextdataMarkerListDataGridView_Click", null, null);
            markerListAccessor.Call("pageNumdataMarkerListDataGridView_ValueChanged", null, null);
            markerListAccessor.Call("prevdataMarkerListDataGridView_Click", null, null);
            markerListAccessor.Call("lastdataMarkerListDataGridView_Click", null, null);
            markerListAccessor.Call("dataMarkerListDataGridView_Sorted", null, null);

        }

        [Test]
        public void TestAttachListener()
        {
            MarkerListController ctl = (MarkerListController)(markerList.getController());
            markerList.AttachListener(ctl);
        }
    }
}
