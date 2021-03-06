using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;
using System;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class MemberOpFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/T/7Pg", "/4DI0A")]
        internal static MemberOp CreateMemberOp01()
        {
            MemberOp memberOp = new MemberOp();
            return memberOp;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateMemberOp01()
        {
            MemberOp memberOp = CreateMemberOp01();
            Assert.IsNotNull(memberOp);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((bool)memberOp.IsFunction);
            recorder.Record((OperatorPriority)memberOp.Priority);
            recorder.FinishRecording();
            #endregion
        }

    }
}
