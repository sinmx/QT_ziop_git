using Dottest.Framework;
using NUnit.Framework;
using OPCTrendLib.OPCData;
using System;

namespace DotTest.Factories.OPCTrendLib.OPCData
{
    [TestFixture(), ObjectFactoryType()]
    public class CancelCompleteEventArgsFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/MNd4Q", "/BrnVw")]
        public static CancelCompleteEventArgs CreateCancelCompleteEventArgs01()
        {
            int transactionIDp = -1;
            int groupHandleClientp = int.MaxValue;
            CancelCompleteEventArgs cancelCompleteEventArgs = new CancelCompleteEventArgs(transactionIDp, groupHandleClientp);
            return cancelCompleteEventArgs;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateCancelCompleteEventArgs01()
        {
            CancelCompleteEventArgs cancelCompleteEventArgs = CreateCancelCompleteEventArgs01();
            Assert.IsNotNull(cancelCompleteEventArgs);
        }

        [ObjectFactoryMethod]
        [HashCode("/MNd4Q", "/b7krA")]
        public static CancelCompleteEventArgs CreateCancelCompleteEventArgs02()
        {
            int transactionIDp = int.MaxValue;
            int groupHandleClientp = 0;
            CancelCompleteEventArgs cancelCompleteEventArgs = new CancelCompleteEventArgs(transactionIDp, groupHandleClientp);
            return cancelCompleteEventArgs;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateCancelCompleteEventArgs02()
        {
            CancelCompleteEventArgs cancelCompleteEventArgs = CreateCancelCompleteEventArgs02();
            Assert.IsNotNull(cancelCompleteEventArgs);
        }

        [ObjectFactoryMethod]
        [HashCode("/MNd4Q", "/4tuHA")]
        public static CancelCompleteEventArgs CreateCancelCompleteEventArgs03()
        {
            int transactionIDp = 1;
            int groupHandleClientp = 1;
            CancelCompleteEventArgs cancelCompleteEventArgs = new CancelCompleteEventArgs(transactionIDp, groupHandleClientp);
            return cancelCompleteEventArgs;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateCancelCompleteEventArgs03()
        {
            CancelCompleteEventArgs cancelCompleteEventArgs = CreateCancelCompleteEventArgs03();
            Assert.IsNotNull(cancelCompleteEventArgs);
        }

    }
}