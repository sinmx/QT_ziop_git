using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;
using System;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class BinaryOpExecutorFactory
    {
        [ObjectFactoryMethod]
        [HashCode("+XI6jg", "+NLaxA")]
        internal static BinaryOpExecutor CreateBinaryOpExecutor01()
        {
            BinaryOpExecutor binaryOpExecutor = new BinaryOpExecutor();
            return binaryOpExecutor;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateBinaryOpExecutor01()
        {
            BinaryOpExecutor binaryOpExecutor = CreateBinaryOpExecutor01();
            Assert.IsNotNull(binaryOpExecutor);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((int)ReflectionAccessor.Wrap(binaryOpExecutor).GetProperty("CurrentIndex"));
            recorder.FinishRecording();
            #endregion
        }

    }
}
