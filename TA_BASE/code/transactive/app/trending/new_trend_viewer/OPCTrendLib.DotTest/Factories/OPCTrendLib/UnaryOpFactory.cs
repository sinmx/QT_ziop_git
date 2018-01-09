using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class UnaryOpFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/enI6w", "+Ayomg")]
        internal static UnaryOp CreateUnaryOp01()
        {
            Token type = Token.ArithmeticFirst;
            UnaryOp unaryOp = UnaryOp.CreateOp(type);
            return unaryOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateUnaryOp01()
        {
            UnaryOp unaryOp = CreateUnaryOp01();
            Assert.IsNull(unaryOp);           
        }

        [ObjectFactoryMethod]
        [HashCode("/enI6w", "+olYiw")]
        internal static UnaryOp CreateUnaryOp02()
        {
            Token type = Token.BooleanNot;
            UnaryOp unaryOp = UnaryOp.CreateOp(type);
            return unaryOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateUnaryOp02()
        {
            UnaryOp unaryOp = CreateUnaryOp02();
            unaryOp.ToString();
            Assert.IsNotNull(unaryOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((OperatorPriority)unaryOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/enI6w", "+KdO4w")]
        internal static UnaryOp CreateUnaryOp03()
        {
            Token type = Token.BitwiseNot;
            UnaryOp unaryOp = UnaryOp.CreateOp(type);
            return unaryOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateUnaryOp03()
        {
            UnaryOp unaryOp = CreateUnaryOp03();
            Assert.IsNotNull(unaryOp);

        }

    }
}