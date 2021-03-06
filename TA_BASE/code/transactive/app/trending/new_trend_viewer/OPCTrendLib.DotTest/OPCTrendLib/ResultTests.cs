using Dottest.Framework;
using NUnit.Framework;
using OPCTrendLib;
//using STEE.ISCS.Log.DotTest.Factories;
using System;

namespace DotTest.OPCTrendLib
{
    [TestFixture()]
    public class ResultTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/W7kmg", "+w6h4A")]
        public void TestResultConstructor01()
        {
            //object value1 = LogLevelFactory.CreateLogLevel01();
            Result result = new Result("RES");
            result.ToString();
        }

        [ExpectedException(typeof(System.InvalidOperationException))]
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestSetType01()
        {
            //object value1 = LogLevelFactory.CreateLogLevel01();
            Result result = new Result("RES");
            result.Type = typeof(System.String);
        }
        
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestSetType02()
        {
            //object value1 = LogLevelFactory.CreateLogLevel01();
            Result result = new Result("RES");
            result.Value = null;
            result.ToString();
            result.Type = typeof(System.String);
        }

                   



    }
}
