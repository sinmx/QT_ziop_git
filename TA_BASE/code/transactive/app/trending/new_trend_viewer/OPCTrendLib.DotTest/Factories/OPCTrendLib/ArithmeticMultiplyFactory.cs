using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class ArithmeticMultiplyFactory
    {
        [ObjectFactoryMethod]
        [HashCode("+/h9mw", "+dOqNQ")]
        internal static ArithmeticMultiply CreateArithmeticMultiply01()
        {
            ArithmeticMultiply arithmeticMultiply = new ArithmeticMultiply();
            arithmeticMultiply.ToString();
            return arithmeticMultiply;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateArithmeticMultiply01()
        {
            ArithmeticMultiply arithmeticMultiply = CreateArithmeticMultiply01();
            Assert.IsNotNull(arithmeticMultiply);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)arithmeticMultiply.Priority);
            recorder.FinishRecording();
            #endregion
        }

    }
}
