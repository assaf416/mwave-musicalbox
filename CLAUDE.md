# MWAVE Musical Box - Project-Specific Workflow

This document extends the global `/projects/CLAUDE.md` with project-specific conventions for MWAVE Musical Box.

---

## Issues-First Workflow (Hebrew)

**All new features and bug fixes start as GitHub issues BEFORE coding.**

### Issue Workflow

1. **Create Issue** (Hebrew language):
   - Use `.github/ISSUE_TEMPLATE/feature_request.md` or `bug_report.md`
   - Include: description, time estimate, fix plan, acceptance criteria
   - GitHub automatically uses these templates when creating new issues

2. **Plan & Document**:
   - Add time estimation (hours/days)
   - Write detailed fix plan with steps
   - Link to relevant code files/directories
   - Add status checkboxes: תוכנן → בעבודה → בדיקה → גמור

3. **Implement**:
   - Create feature branch: `feature/<issue-number>-<slug>` or `bug/<issue-number>-<slug>`
   - Add comprehensive unit tests (maximize coverage)
   - Update issue status to "בעבודה" (In Progress)
   - Link PR to issue when created

4. **Test & Complete**:
   - Add unit tests for every change
   - Run full test suite before closing
   - Update issue status to "גמור" (Completed)
   - Add links to test files in issue

### Hebrew Issue Labels
- `feature` - תכונה חדשה
- `bug` - באג/כשל
- `enhancement` - שיפור
- `documentation` - תיעוד
- `test` - בדיקה

---

## Development Stack

| Component | Technology | Notes |
|-----------|-----------|-------|
| **Language** | C++17 | firmware & emulator |
| **Build** | CMake 3.20+ | cross-platform |
| **Testing** | Google Test (gtest) | unit tests |
| **Repo** | github.com/assaf416/mwave-musicalbox | main repository |

---

## Repository Structure

```
mwave-musicalbox/
├── .github/ISSUE_TEMPLATE/     # Issue templates (Hebrew)
│   ├── feature_request.md
│   └── bug_report.md
├── emulator/                   # Console-based emulator
│   ├── CMakeLists.txt
│   ├── src/                    # Source files (.cpp)
│   └── tests/                  # Unit tests
├── firmware/                   # STM32H7 firmware
│   ├── include/
│   └── src/
├── tests/                      # Integration tests
├── docs/                       # Documentation
└── plan.json                   # Cucumber stories + tracking
```

---

## Testing Requirements

### Unit Tests
- **Framework**: Google Test (gtest)
- **Location**: `emulator/tests/` and `firmware/tests/`
- **Coverage**: Aim for 80%+ code coverage
- **Naming**: `test_*.cpp` or `*_test.cpp`
- **Run**: `ctest --output-on-failure`

### Example Test File Structure
```cpp
// tests/test_synth_emulator.cpp
#include <gtest/gtest.h>
#include "synth_emulator.h"

class SynthEmulatorTest : public ::testing::Test {
protected:
  SynthEmulator synth;
};

TEST_F(SynthEmulatorTest, PlayNoteChangesActiveVoices) {
  synth.playNote(60, 100);
  EXPECT_GT(synth.getActiveVoiceCount(), 0);
}
```

### Test Execution
Before closing any issue:
1. Build all tests: `cmake -DBUILD_TESTS=ON .. && make test`
2. Run tests: `ctest --output-on-failure -V`
3. Report coverage (optional): `gcov` or `lcov`
4. Link test results in GitHub issue

---

## Branching Strategy

**Branch Types**:
- `feature/<issue-number>-<slug>` - New features
- `bug/<issue-number>-<slug>` - Bug fixes
- `enhancement/<issue-number>-<slug>` - Improvements
- `master` - Main development branch

**Example**:
- Issue #2: `feature/2-melotron-sf2-integration`
- Issue #5: `bug/5-reverb-distortion-fix`

**PR Requirements**:
- Link to issue: `Closes #<number>` in PR body
- Include test results
- Reference any new test files
- Squash commits before merge

---

## Issue Status Tracking

**Hebrew Status Labels**:
- ✅ **תוכנן** (Planned) - Issue created, not started
- 🔄 **בעבודה** (In Progress) - Actively being worked on
- 🧪 **בדיקה** (Testing) - In testing/review phase
- ✨ **גמור** (Completed) - Issue resolved and merged

**Update Timing**:
1. Create issue → Mark "תוכנן"
2. Start work → Mark "בעבודה"
3. Submit PR → Mark "בדיקה"
4. Merge PR → Mark "גמור"

---

## Documentation Requirements

Every issue must include:
- **תיאור**: Clear description in Hebrew
- **תוכנית הפתרון**: Step-by-step fix plan
- **דרישות**: Implementation requirements
- **בדיקות**: Test/acceptance criteria
- **הערכת זמן**: Time estimate (hours/days)

After completion, link:
- PR URL (GitHub)
- Test file(s) location
- Any new documentation

---

## CI/CD Checklist

Before marking issue as "גמור" (Completed):
- [ ] All tests pass locally
- [ ] Code builds without warnings
- [ ] New tests added for feature/fix
- [ ] Issue links to PR
- [ ] PR links back to issue
- [ ] Hebrew documentation updated
- [ ] No breaking changes to existing code

---

## Example Issue Workflow

1. **Create Issue**: "הוסף תמיכה בעיבוד אודיו ב-PortAudio"
   - Type: Feature
   - Estimate: 4 hours
   - Plan: 3 clear steps
   - Tests: 2-3 test cases defined

2. **Create Branch**: `feature/8-portaudio-integration`

3. **Develop**:
   - Add code to `emulator/src/audio_output.cpp`
   - Add tests to `emulator/tests/test_audio_output.cpp`
   - Run tests locally

4. **Submit PR**:
   - Title: "Add PortAudio integration"
   - Body: "Closes #8"
   - Link test file

5. **Complete**:
   - Merge PR
   - Update issue status to "גמור"
   - Celebrate! 🎉

---

## Resources

| Item | Location | Purpose |
|------|----------|---------|
| Issue Templates | `.github/ISSUE_TEMPLATE/` | Hebrew templates for features/bugs |
| Project Plan | `plan.json` | Cucumber stories + tracking |
| Build Guide | `DEVELOPMENT.md` | Setup & compilation |
| CC Reference | `MWAVE-CC-Parameter-Reference.md` | MIDI parameter mappings |
| Melotron Integration | `MELOTRON_INTEGRATION.md` | SoundFont2 details |

---

## Notes

- All issues should be in **Hebrew**
- Time estimates help with sprint planning
- Tests are **mandatory**, not optional
- Link PRs to issues for traceability
- Update status regularly for transparency

---

**Version**: 1.0  
**Last Updated**: November 21, 2026  
**Repository**: https://github.com/assaf416/mwave-musicalbox
