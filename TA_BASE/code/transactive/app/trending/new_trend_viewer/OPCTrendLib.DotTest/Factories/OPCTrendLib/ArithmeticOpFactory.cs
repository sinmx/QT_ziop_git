using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class ArithmeticOpFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/RKKHw", "+J19Sg")]
        internal static ArithmeticOp CreateArithmeticOp01()
        {
            ArithmeticOp arithmeticOp = new ArithmeticModulus();
            return arithmeticOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateArithmeticOp01()
        {
            ArithmeticOp arithmeticOp = CreateArithmeticOp01();
            Assert.IsNotNull(arithmeticOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)arithmeticOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/RKKHw", "+DlJDQ")]
        internal static ArithmeticOp CreateArithmeticOp02()
        {
            ArithmeticOp arithmeticOp = new ArithmeticSubtract();
            return arithmeticOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateArithmeticOp02()
        {
            ArithmeticOp arithmeticOp = CreateArithmeticOp02();
            Assert.IsNotNull(arithmeticOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)arithmeticOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/RKKHw", "+zQTKQ")]
        internal static ArithmeticOp CreateArithmeticOp03()
        {
            ArithmeticOp arithmeticOp = new ArithmeticDivide();
            return arithmeticOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateArithmeticOp03()
        {
            ArithmeticOp arithmeticOp = CreateArithmeticOp03();
            Assert.IsNotNull(arithmeticOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)arithmeticOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

    }
}
