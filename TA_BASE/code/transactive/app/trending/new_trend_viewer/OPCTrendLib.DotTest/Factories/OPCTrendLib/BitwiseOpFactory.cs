using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class BitwiseOpFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/ZDoFQ", "/Pb08w")]
        internal static BitwiseOp CreateBitwiseOp01()
        {
            BitwiseOp bitwiseOp = new BitwiseOr();
            return bitwiseOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBitwiseOp01()
        {
            BitwiseOp bitwiseOp = CreateBitwiseOp01();
            Assert.IsNotNull(bitwiseOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)bitwiseOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/ZDoFQ", "+6Sg2w")]
        internal static BitwiseOp CreateBitwiseOp02()
        {
            BitwiseOp bitwiseOp = new BitwiseXor();
            return bitwiseOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBitwiseOp02()
        {
            BitwiseOp bitwiseOp = CreateBitwiseOp02();
            Assert.IsNotNull(bitwiseOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)bitwiseOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/ZDoFQ", "+20aHw")]
        internal static BitwiseOp CreateBitwiseOp03()
        {
            BitwiseOp bitwiseOp = new BitwiseAnd();
            return bitwiseOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBitwiseOp03()
        {
            BitwiseOp bitwiseOp = CreateBitwiseOp03();
            Assert.IsNotNull(bitwiseOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)bitwiseOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

    }
}