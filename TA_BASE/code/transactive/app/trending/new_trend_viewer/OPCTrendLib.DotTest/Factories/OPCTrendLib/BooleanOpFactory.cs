using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class BooleanOpFactory
    {
        [ObjectFactoryMethod]
        [HashCode("//5VDg", "+iYU6w")]
        internal static BooleanOp CreateBooleanOp01()
        {
            BooleanOp booleanOp = new BooleanAnd();
            return booleanOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBooleanOp01()
        {
            BooleanOp booleanOp = CreateBooleanOp01();
            Assert.IsNotNull(booleanOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)booleanOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("//5VDg", "+4WEww")]
        internal static BooleanOp CreateBooleanOp02()
        {
            BooleanOp booleanOp = new BooleanOr();
            return booleanOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBooleanOp02()
        {
            BooleanOp booleanOp = CreateBooleanOp02();
            Assert.IsNotNull(booleanOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)booleanOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

    }
}
