using Dottest.Framework;
using NUnit.Framework;
using STEE.ISCS.MVC;
using STEE.ISCS.MVC.DotTest.Factories;
using System;
using System.Collections.Generic;

namespace STEE.ISCS.MVC.DotTest
{
    [TestFixture()]
    public class ViewManagerTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/ISZyQ", "+Xw4nA")]
        public void TestViewManagerConstructor01()
        {
            //ViewManager viewManager = (ViewManager)ReflectionAccessor.Construct();
            ViewManager viewManager = ViewManagerFactory.CreateViewManager01();

            //Post Check
            Assert.IsNotNull(viewManager);
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/h0CEw", "+2cynA")]
        public void TestGetInstance01()
        {
            ViewManager viewManager = ViewManager.GetInstance();

             //Post Check
            Assert.IsNotNull(viewManager);        
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/ugo4Q", "+69UHQ")]
        public void TestGetView01()
        {
            ViewManager viewManager = ViewManagerFactory.CreateViewManager01();
            string type = string.Empty;
            IView view = viewManager.GetView(type);

             //Post Check
            Assert.IsNull(view);
        
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("+70V5w", "+RRIQg")]
        public void TestGetView02()
        {
            ViewManager viewManager = ViewManagerFactory.CreateViewManager01();
            ViewFactoryTest testfactory = new ViewFactoryTest();
            viewManager.RegisterViewFactory(testfactory);
            string type = ViewTest.ViewTestType;
            string id = string.Empty;

            //Test Procedure Call
            IView view = viewManager.GetView(type, id);
            IView view1 = viewManager.GetView(type);

            //Post Check
            Assert.IsNotNull(view);
            Assert.IsNotNull(view1);            
            Assert.AreEqual(view1, view);
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/tENeA", "+5FDOg")]
        public void TestcreateView01()
        {
            ViewManager viewManager = ViewManagerFactory.CreateViewManager01();
            string type = string.Empty;
            string id = string.Empty;
            Accessor viewManagerAccessor = ReflectionAccessor.Wrap(viewManager);
            //Test Procedure Call
            IView view = (IView)viewManagerAccessor.Call("createView", type, id);
            //Post Check
            Assert.IsNull(view);

            //test 2

            ViewFactoryTest testfactory = new ViewFactoryTest();
            viewManager.RegisterViewFactory(testfactory);
            type = ViewTest.ViewTestType;            
            //Test Procedure Call
            view = (IView)viewManagerAccessor.Call("createView", type, id);
            //Post Check
            Assert.IsNotNull(view);

        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestUnregisterView01()
        {
            //Initial setup
            ViewManager viewManager = ViewManagerFactory.CreateViewManager01();
            ViewFactoryTest testfactory = new ViewFactoryTest();
            viewManager.RegisterViewFactory(testfactory);
            string type = ViewTest.ViewTestType;
            string id = string.Empty;
            IView view = viewManager.GetView(type, id);
            //Test Method call
            viewManager.UnregisterView(view);

            //Post Check
            Accessor viewManagerAccessor = ReflectionAccessor.Wrap(viewManager);
            Dictionary<string, IView> viewMap = (Dictionary<string, IView>)viewManagerAccessor.GetField("m_ViewMap");
            Assert.AreEqual(0, viewMap.Count);
        }

    }
}
