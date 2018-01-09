using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class BooleanAndFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/FVo9g", "+iYU6w")]
        internal static BooleanAnd CreateBooleanAnd01()
        {
            BooleanAnd booleanAnd = new BooleanAnd();
            booleanAnd.ToString();
            return booleanAnd;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBooleanAnd01()
        {
            BooleanAnd booleanAnd = CreateBooleanAnd01();
            Assert.IsNotNull(booleanAnd);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)booleanAnd.Priority);
            recorder.FinishRecording();
            #endregion
        }

    }
}