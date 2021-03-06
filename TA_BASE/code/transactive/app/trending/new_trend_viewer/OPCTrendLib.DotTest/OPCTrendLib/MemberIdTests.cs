using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;

namespace DotTest.OPCTrendLib
{
    [TestFixture()]
    public class MemberIdTests
    {
        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        [HashCode("/n6qJA", "/cKZrw")]
        public void TestEval01()
        {
            MemberId memberid = new MemberId("Name1");
            memberid.ToString();
            Result[] arrRes = new Result[0];
            //Test Procedure Call
            Result result = memberid.Eval(new Evaluator(), arrRes);
            //Post Condition Check
            Assert.AreEqual("Name1", result.Value);
        }
    }
}
